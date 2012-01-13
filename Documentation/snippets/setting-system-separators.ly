%% DO NOT EDIT this file manually; it is automatically
%% generated from LSR http://lsr.dsi.unimi.it
%% Make any changes in LSR itself, or in Documentation/snippets/new/ ,
%% and then run scripts/auxiliar/makelsr.py
%%
%% This file is in the public domain.
\version "2.14.0"

\header {
  lsrtags = "staff-notation, tweaks-and-overrides, paper-and-layout"

%% Translation of GIT committish: 6977ddc9a3b63ea810eaecb864269c7d847ccf98
  texidoces = "
Se pueden insertar separadores sistema entre los sistemas de una
página.  Se puede usar cualquier elemento de marcado, pero
@code{\\slashSeparator} está disponible como una elección
predeterminada adecuada.

"
  doctitlees = "Fijar un separador entre los sistemas"



  texidoc = "
System separators can be inserted between systems.  Any markup can be
used, but @code{\\slashSeparator} has been provided as a sensible
default.

"
  doctitle = "Setting system separators"
} % begin verbatim

\paper {
  system-separator-markup = \slashSeparator
}

notes = \relative c' {
  c1 | c \break
  c1 | c \break
  c1 | c
}

\book {
  \score {
    \new GrandStaff <<
      \new Staff \notes
      \new Staff \notes
    >>
  }
}

