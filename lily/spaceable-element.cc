/*   
  spaceable-element.cc --  implement Spaceable_element
  
  source file of the GNU LilyPond music typesetter
  
  (c) 2000 Han-Wen Nienhuys <hanwen@cs.uu.nl>
  
 */

#include "spaceable-element.hh"
#include "score-element.hh"
#include "warn.hh"

SCM
Spaceable_element::get_minimum_distances ( Score_element*me)
{
  return me->get_elt_property ("minimum-distances");
}

/*todo: merge code of spring & rod?
 */
void
Spaceable_element::add_rod (Score_element *me , Score_element * p, Real d)
{
  SCM mins = get_minimum_distances (me);
  SCM newdist = gh_double2scm (d);
  for (SCM s = mins; gh_pair_p (s); s = gh_cdr (s))
    {
      SCM dist = gh_car (s);
      if (gh_car (dist) == p->self_scm ())
	{
	  gh_set_cdr_x (dist, scm_max (gh_cdr (dist),
				       newdist));
	  return ;
	}
    }

  mins = gh_cons (gh_cons (p->self_scm (), newdist), mins);
  me->set_elt_property ("minimum-distances", mins);
}

void
Spaceable_element::add_spring (Score_element*me, Score_element * p, Real d, Real strength)
{
  SCM mins = get_ideal_distances (me);
  SCM newdist= gh_double2scm (d);
  for (SCM s = mins; gh_pair_p (s); s = gh_cdr (s))
    {
      SCM dist = gh_car (s);
      if (gh_car (dist) == p->self_scm ())
	{
	  programming_error("already have that spring");
	  return ;
	}
    }
  SCM newstrength= gh_double2scm (strength);  
  
  mins = gh_cons (gh_cons (p->self_scm (), gh_cons (newdist, newstrength)), mins);
  me->set_elt_property ("ideal-distances", mins);
}

SCM
Spaceable_element::get_ideal_distances (Score_element*me)
{
  return me->get_elt_property ("ideal-distances");
}


void
Spaceable_element::remove_interface (Score_element*me)
{
  me->remove_elt_property ("minimum-distances");
  me->remove_elt_property ("ideal-distances");
  me->remove_elt_property ("dir-list");
}


void
Spaceable_element::set_interface (Score_element*me)
{
}
