/*
  chord-name-engraver.cc -- implement Chord_name_engraver

  source file of the GNU LilyPond music typesetter

  (c) 1998--2002 Jan Nieuwenhuizen <janneke@gnu.org>
*/

#include "engraver.hh"
#include "chord-name.hh"
#include "chord.hh"
#include "musical-request.hh"
#include "paper-def.hh"
#include "font-interface.hh"
#include "paper-def.hh"
#include "main.hh"
#include "dimensions.hh"
#include "item.hh"
#include "pitch.hh"
#include "protected-scm.hh"

class Chord_name_engraver : public Engraver 
{

  TRANSLATOR_DECLARATIONS( Chord_name_engraver);

protected:
  virtual void stop_translation_timestep ();
  virtual void acknowledge_grob (Grob_info i);
  virtual void process_acknowledged_grobs ();
  virtual bool try_music (Music *);

private:
  void add_note (Note_req *);
  
  Item* chord_name_p_;

  Protected_scm chord_;
  Protected_scm last_chord_;
};



Chord_name_engraver::Chord_name_engraver ()
{
  chord_name_p_ = 0;
  chord_ = gh_cons (SCM_EOL, gh_cons (SCM_EOL, SCM_EOL));
  last_chord_ = chord_;
}

void
Chord_name_engraver::add_note (Note_req* n)
{
  SCM pitches = ly_car (chord_);
  SCM modifiers = ly_cdr (chord_);
  SCM inversion = modifiers == SCM_EOL ? SCM_EOL : ly_car (modifiers);
  SCM bass = modifiers == SCM_EOL ? SCM_EOL : ly_cdr (modifiers);
  
  if (n->get_mus_property ("inversion") == SCM_BOOL_T)
    inversion = n->get_mus_property ("pitch");
  else if (n->get_mus_property ("bass") == SCM_BOOL_T)
    bass = n->get_mus_property ("pitch");
  else
    pitches = scm_sort_list (gh_cons (n->get_mus_property ("pitch"), pitches),
			     Pitch::less_p_proc);
  chord_ = gh_cons (pitches, gh_cons (inversion, bass));
}

bool
Chord_name_engraver::try_music (Music* m)
{
  if (Note_req* n = dynamic_cast<Note_req*> (m))
    {
      add_note (n);
      return true;
    }
  return false;
}

void
Chord_name_engraver::acknowledge_grob (Grob_info i)
{
  if (Note_req* n = dynamic_cast<Note_req*> (i.music_cause ()))
    add_note (n);
}

void
Chord_name_engraver::process_acknowledged_grobs ()
{
  if (!chord_name_p_ && ly_car (chord_) != SCM_EOL)
    {
      chord_name_p_ = new Item (get_property ("ChordName"));
      chord_name_p_->set_grob_property ("chord", chord_);
      announce_grob(chord_name_p_, SCM_EOL);
      SCM s = get_property ("chordChanges");
      if (to_boolean (s) && ly_car (last_chord_) != SCM_EOL
	  	  && gh_equal_p (chord_, last_chord_))
	chord_name_p_->set_grob_property ("begin-of-line-visible", SCM_BOOL_T);
    }
}

void
Chord_name_engraver::stop_translation_timestep ()
{
  if (chord_name_p_)
    {
      typeset_grob (chord_name_p_);
    }
  chord_name_p_ = 0;

  if (ly_car (chord_) != SCM_EOL)
    last_chord_ = chord_;
  chord_ = gh_cons (SCM_EOL, gh_cons (SCM_EOL, SCM_EOL));
}

ENTER_DESCRIPTION(Chord_name_engraver,
/* descr */       "Catch Note_req's, Tonic_reqs, Inversion_reqs, Bass_req
and generate the appropriate chordname.",
/* creats*/       "ChordName",
/* acks  */       "grob-interface",
/* reads */       "chordChanges",
/* write */       "");
