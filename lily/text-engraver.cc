/*   
  text-engraver.cc --  implement Text_engraver
  
  source file of the GNU LilyPond music typesetter
  
  (c) 1998--2000 Han-Wen Nienhuys <hanwen@cs.uu.nl>
  
 */


#include "engraver.hh"
#include "side-position-interface.hh"
#include "item.hh"
#include "musical-request.hh"
#include "stem.hh"
#include "rhythmic-head.hh"

/**
   typeset directions that are  plain text.
 */
class Text_engraver : public Engraver
{
  Link_array<Text_script_req> reqs_;
  Link_array<Item> texts_;
public:
  VIRTUAL_COPY_CONS(Translator);
protected:
  virtual bool do_try_music (Music* m);
  virtual void do_pre_move_processing ();
  virtual void do_post_move_processing ();
  virtual void do_process_music ();
  virtual void acknowledge_element (Score_element_info);
};


bool
Text_engraver::do_try_music (Music *m)
{
  if (Text_script_req *r = dynamic_cast<Text_script_req*> (m))
    {
      reqs_.push (r);
      return true;
    }
  return false;
}


void
Text_engraver::acknowledge_element (Score_element_info inf)
{
  if (Rhythmic_head::has_interface (inf.elem_l_))
    {
      for (int i=0; i < texts_.size (); i++)
	{
	  Score_element*t = texts_[i];
	  Side_position::add_support (t,inf.elem_l_);
	  if (Side_position::get_axis( t) == X_AXIS
	      && !t->parent_l (Y_AXIS))
	    t->set_parent (inf.elem_l_, Y_AXIS);
	}
    }
  if (Stem::has_interface (inf.elem_l_))
    {
      for (int i=0; i < texts_.size (); i++)
	{
	  Side_position::add_support(texts_[i],inf.elem_l_);
	}
    }
}

void
Text_engraver::do_process_music ()
{
  for (int i=0; i < reqs_.size (); i++)
    {
      Text_script_req * r = reqs_[i];

      Item *text = new Item (get_property ("basicTextScriptProperties"));
      

      SCM axisprop = get_property ("scriptHorizontal");

      Side_position::set_axis (text, to_boolean (axisprop) ? X_AXIS : Y_AXIS);

      /*
	make sure they're in order by adding i to the priority field.
	*/
      text->set_elt_property ("script-priority",
			    gh_int2scm (200 + i));

      if (r->get_direction ())
	Side_position::set_direction (text, r->get_direction ());
      
      text->set_elt_property ("text",
			      ly_str02scm ( r->text_str_.ch_C ()));
      
      if (r->style_str_.length_i ())
	text->set_elt_property ("style", ly_str02scm (r->style_str_.ch_C()));
      
      /*
       Text is empty by default, which means that the only condition
       for not setting 'no-spacing-rods' should be: boolean && true.

       Anyway, non-empty text has been broken for some time now.
       */
      SCM nonempty = get_property ("textNonEmpty");
      if (!to_boolean (nonempty))
	/*
	  empty text: signal that no rods should be applied.  
	 */
	text->set_elt_property ("no-spacing-rods" , SCM_BOOL_T);

		
      announce_element (text, r);
      texts_.push (text);
    }
}

void
Text_engraver::do_pre_move_processing ()
{
  for (int i=0; i < texts_.size (); i++)
    {
      Item *ti = texts_[i];
      Side_position::add_staff_support (ti);
      typeset_element (ti);
    }
  texts_.clear ();
}

void
Text_engraver::do_post_move_processing ()
{
  reqs_.clear ();
}

ADD_THIS_TRANSLATOR(Text_engraver);

