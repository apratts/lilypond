/*
  rest.cc -- implement Rest

  source file of the GNU LilyPond music typesetter

  (c)  1997--1999 Han-Wen Nienhuys <hanwen@cs.uu.nl>
*/

#include "molecule.hh"
#include "paper-def.hh"
#include "lookup.hh"
#include "rest.hh"
#include "dots.hh"
#include "axis-group-element.hh"
#include "paper-score.hh"

void
Rest::do_add_processing ()
{
  if (balltype_i_ == 0)
    position_i_ += 2;		// guh.

  Rhythmic_head::do_add_processing ();
}

void
Rest::do_post_processing ()
{
  Rhythmic_head::do_post_processing ();
  if (dots_l_
      && balltype_i_ > 4) // UGH.
    {
      /*
	UGH. 
       */
      if (balltype_i_ == 7)
	dots_l_->set_position (4);
      else
	dots_l_->set_position (3);
    }
}


Molecule *
Rest::do_brew_molecule_p () const
{
  bool ledger_b =false;

  if (balltype_i_ == 0 || balltype_i_ == 1)
    ledger_b = abs(position_f ()  - (2* balltype_i_ - 1)) > lines_i (); 

  
  String style; 
  SCM style_sym =get_elt_property ("style");
  if (balltype_i_ >= 2 && style_sym != SCM_UNDEFINED)
    {
      style = ly_scm2string (style_sym);
    }
  
  Molecule s(lookup_l ()->rest (balltype_i_, ledger_b, style));
  Molecule * m = new Molecule ( Molecule (s));

  return m;
}



