%% Do not edit this file; it is auto-generated from input/new
%% This file is in the public domain.
\version "2.11.66"
\header {
  lsrtags = "staff-notation"
  texidoc = "
'Tick' bar lines are often used in music where the bar line is used
only for coordination and is not meant to imply any rhythmic stress.
"
  doctitle = "Tick bar lines"
} % begin verbatim

\relative c' {
  \set Score.defaultBarType = #"'"
  c4 d e f
  g4 f e d
  c4 d e f
  g4 f e d
  \bar "|."
}
