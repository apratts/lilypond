/*
  paper-outputter-scheme.cc -- implement Paper_outputter bindings

  source file of the GNU LilyPond music typesetter

  (c) 2005 Han-Wen Nienhuys <hanwen@xs4all.nl>
*/

#include "paper-outputter.hh"
#include "warn.hh"
#include "stencil.hh"

LY_DEFINE (ly_make_paper_outputter, "ly:make-paper-outputter",
	   2, 0, 0, (SCM outname, SCM format),
	   "Create an outputter that evaluates within "
	   "@code{output-}@var{format}, writing to file @var{outname}.")
{
  SCM_ASSERT_TYPE (scm_is_string (outname), outname, SCM_ARG1, __FUNCTION__,
		   "String");
  SCM_ASSERT_TYPE (scm_is_string (format), format, SCM_ARG2, __FUNCTION__,
		   "String");

  String outname_str = ly_scm2string (outname);
  String f = ly_scm2string (format);

  progress_indication (_f ("Layout output to `%s'...",
			   outname_str == "-"
			   ? String ("<stdout>")
			   : outname_str));
  progress_indication ("\n");
  Paper_outputter *po = new Paper_outputter (outname_str, f);

  scm_gc_unprotect_object (po->self_scm ());
  return po->self_scm ();
}

/* FIXME: why is output_* wrapper called dump?  */
LY_DEFINE (ly_outputter_dump_stencil, "ly:outputter-dump-stencil",
	   2, 0, 0, (SCM outputter, SCM stencil),
	   "Dump stencil @var{expr} onto @var{outputter}.")
{
  Paper_outputter *po = unsmob_outputter (outputter);
  Stencil *st = unsmob_stencil (stencil);
  SCM_ASSERT_TYPE (po, outputter, SCM_ARG1, __FUNCTION__, "Paper_outputter");
  SCM_ASSERT_TYPE (st, stencil, SCM_ARG1, __FUNCTION__, "Paper_outputter");
  po->output_stencil (*st);
  return SCM_UNSPECIFIED;
}

LY_DEFINE (ly_outputter_dump_string, "ly:outputter-dump-string",
	   2, 0, 0, (SCM outputter, SCM str),
	   "Dump @var{str} onto @var{outputter}.")
{
  Paper_outputter *po = unsmob_outputter (outputter);
  SCM_ASSERT_TYPE (po, outputter, SCM_ARG1, __FUNCTION__, "Paper_outputter");
  SCM_ASSERT_TYPE (scm_is_string (str), str, SCM_ARG1, __FUNCTION__, "Paper_outputter");

  return po->dump_string (str);
}

LY_DEFINE (ly_outputter_port, "ly:outputter-port",
	   1, 0, 0, (SCM outputter),
	   "Return output port for @var{outputter}.")
{
  Paper_outputter *po = unsmob_outputter (outputter);
  SCM_ASSERT_TYPE (po, outputter, SCM_ARG1, __FUNCTION__, "Paper_outputter");

  return po->file ();
}

LY_DEFINE (ly_outputter_close, "ly:outputter-close",
	   1, 0, 0, (SCM outputter),
	   "Close port of @var{outputter}.")
{
  Paper_outputter *po = unsmob_outputter (outputter);
  SCM_ASSERT_TYPE (po, outputter, SCM_ARG1, __FUNCTION__, "Paper_outputter");

  po->close ();
  return SCM_UNSPECIFIED;
}
