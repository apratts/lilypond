/*
  paper-def.cc -- implement Paper_def

  source file of the GNU LilyPond music typesetter

  (c) 1997 Han-Wen Nienhuys <hanwen@stack.nl>
*/

#include <math.h>
#include "string.hh"
#include "assoc.hh"
#include "misc.hh"
#include "paper-def.hh"
#include "debug.hh"
#include "lookup.hh"
#include "dimen.hh"
#include "input-translator.hh"
#include "assoc-iter.hh"
#include "score-grav.hh"
#include "p-score.hh"
#include "main.hh"

void
Paper_def::set_var (String s, Real r)
{
  real_vars_p_->elem (s) = r;
}
 
Real
Paper_def::get_var (String s) const
{
  if (! real_vars_p_->elt_b (s))
    error ("unknown paper variable `"  + s+"'");
  return real_vars_p_->elem (s);
}

Real
Paper_def::linewidth_f() const
{
  return get_var ("linewidth");
}

Real
Paper_def::duration_to_dist (Moment d,Real k) const
{
  if (get_var("geometric"))
    return geometric_spacing(d);
  return arithmetic_spacing(d,k);
}


/**
  Get the measure wide constant for arithmetic.

  @see   
  John S. Gourlay. ``Spacing a Line of Music,'' Technical Report
  OSU-CISRC-10/87-TR35, Department of Computer and Information Science,
  The Ohio State University, 1987.

  */
Real
Paper_def::arithmetic_constant(Moment d) const
{
  return get_var("arithmetic_basicspace") - log_2(Moment(1,8) <? d);
}

Real
Paper_def::arithmetic_spacing(Moment d ,Real k) const
{
  return (log_2(d) + k)* get_var("arithmetic_multiplier");
}

Real
Paper_def::geometric_spacing(Moment d) const
{
  Real dur_f = (d) ?pow (get_var ("geometric"), log_2(d)) : 0;
  return get_var ("basicspace") + get_var ("unitspace")  * dur_f;
}

Paper_def::Paper_def()
{
  itrans_p_ = 0;
  lookup_p_ = 0;
  real_vars_p_ = new Assoc<String,Real>;
}

Paper_def::~Paper_def()
{
  delete itrans_p_;
  delete real_vars_p_;
  delete lookup_p_;
}

Paper_def::Paper_def (Paper_def const&s)
{
  itrans_p_ = s.itrans_p_ ? new Input_translator (*s.itrans_p_):0;
  lookup_p_ = s.lookup_p_? new Lookup (*s.lookup_p_) : 0;
  lookup_p_->paper_l_ = this;
  real_vars_p_ = new Assoc<String,Real> (*s.real_vars_p_);
  outfile_str_ = s.outfile_str_;
}

void
Paper_def::set (Input_translator * itrans_p)
{
  delete itrans_p_;
  itrans_p_  = itrans_p;
}

void
Paper_def::set (Lookup*l)
{
  assert (l != lookup_p_);
  delete lookup_p_;
  lookup_p_ = l;
  lookup_p_->paper_l_ = this;
}

Real
Paper_def::interline_f() const
{
  return get_var ("interline");
}


Real
Paper_def::rule_thickness() const
{
  return get_var ("rule_thickness");
}

Real
Paper_def::interbeam_f() const
{
  return get_var ("interbeam");
}
Real
Paper_def::internote_f() const
{
  return interline_f() / 2; 
}

Real
Paper_def::note_width() const
{
  return get_var ("notewidth");
}

void
Paper_def::print() const
{
#ifndef NPRINT
  DOUT << "Paper {";
  DOUT << "out: " <<outfile_str_;
  lookup_p_->print();
  itrans_p_->print();
  for (Assoc_iter<String,Real> i (*real_vars_p_); i.ok(); i++) 
    {
      DOUT << i.key() << "= " << i.val () << "\n";
    }
  DOUT << "}\n";
#endif
}

Lookup const *
Paper_def::lookup_l()
{
  assert (lookup_p_);
  return lookup_p_;
}

Global_translator*
Paper_def::get_global_translator_p() 
{
  if (only_midi) 
    {
      return 0;
    }

  Global_translator* g =  itrans_p_->get_group_engraver_p()->global_l ();
  assert (g->is_type_b (Score_engraver::static_name()));
  Score_engraver*grav = (Score_engraver*) g;
  grav->pscore_p_ = new Paper_score;
  grav->pscore_p_->paper_l_ = this;
  return g;	  
}

IMPLEMENT_IS_TYPE_B1(Paper_def, Music_output_def);
