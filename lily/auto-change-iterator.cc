/*
  auto-change-iterator.cc -- implement  Auto_change_iterator

  source file of the GNU LilyPond music typesetter

  (c) 1999--2005 Han-Wen Nienhuys <hanwen@cs.uu.nl>
*/

#include "context.hh"
#include "event.hh"
#include "music-wrapper-iterator.hh"
#include "direction.hh"

class Auto_change_iterator : public Music_wrapper_iterator
{
public:
  DECLARE_SCHEME_CALLBACK (constructor, ());

  Auto_change_iterator ();

protected:
  virtual void do_quit ();
  virtual void construct_children ();
  virtual void process (Moment);
  Array<Pitch> pending_pitch (Moment) const;
private:
  SCM split_list_;
  Direction where_dir_;
  void change_to (Music_iterator *, SCM, String);
  Moment start_moment_;

  Interpretation_context_handle up_;
  Interpretation_context_handle down_;

};

void
Auto_change_iterator::change_to (Music_iterator *it, SCM to_type_sym,
				 String to_id)
{
  Context *current = it->get_outlet ();
  Context *last = 0;

  /*
    Cut & Paste from Change_iterator (ugh).

    TODO: abstract this function
  */

  /* find the type  of translator that we're changing.

  If \translator Staff = bass, then look for Staff = *
  */
  while (current && !current->is_alias (to_type_sym))
    {
      last = current;
      current = current->get_parent_context ();
    }

  if (current && current->id_string () == to_id)
    {
      String msg;
      msg += _ ("Can't switch translators, I'm there already");
    }

  if (current)
    if (last)
      {
	Context *dest
	  = it->get_outlet ()->find_create_context (to_type_sym, to_id, SCM_EOL);
	current->remove_context (last);
	dest->add_context (last);
      }
    else
      {
	/*
	  We could change the current translator's id, but that would make
	  errors hard to catch

	*/
      }
  else;

}

void
Auto_change_iterator::process (Moment m)
{
  Music_wrapper_iterator::process (m);

  Moment now = get_outlet ()->now_mom ();
  Moment *splitm = 0;

  for (; scm_is_pair (split_list_); split_list_ = scm_cdr (split_list_))
    {
      splitm = unsmob_moment (scm_caar (split_list_));
      if ((*splitm + start_moment_) > now)
	break;

      SCM tag = scm_cdar (split_list_);
      Direction d = to_dir (tag);

      if (d && d != where_dir_)
	{
	  where_dir_ = d;
	  String to_id = (d >= 0) ? "up" : "down";
	  change_to (child_iter_,
		     ly_symbol2scm ("Staff"),
		     to_id);
	}
    }
}

Auto_change_iterator::Auto_change_iterator ()
{
  where_dir_ = CENTER;
  split_list_ = SCM_EOL;
}

void
Auto_change_iterator::construct_children ()
{
  split_list_ = get_music ()->get_property ("split-list");
  start_moment_ = get_outlet ()->now_mom ();

  SCM props = get_outlet ()->get_property ("trebleStaffProperties");
  Context *up = get_outlet ()->find_create_context (ly_symbol2scm ("Staff"),
						    "up", props);

  props = get_outlet ()->get_property ("bassStaffProperties");
  Context *down = get_outlet ()->find_create_context (ly_symbol2scm ("Staff"),
						      "down", props);

  up_.set_context (up);
  down_.set_context (down);

  Context *voice = up->find_create_context (ly_symbol2scm ("Voice"),
					    "", SCM_EOL);
  set_context (voice);
  Music_wrapper_iterator::construct_children ();

}

void
Auto_change_iterator::do_quit ()
{
  up_.set_context (0);
  down_.set_context (0);

}
IMPLEMENT_CTOR_CALLBACK (Auto_change_iterator);
