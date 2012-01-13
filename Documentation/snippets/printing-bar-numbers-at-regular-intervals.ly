%% DO NOT EDIT this file manually; it is automatically
%% generated from LSR http://lsr.dsi.unimi.it
%% Make any changes in LSR itself, or in Documentation/snippets/new/ ,
%% and then run scripts/auxiliar/makelsr.py
%%
%% This file is in the public domain.
\version "2.14.0"

\header {
  lsrtags = "rhythms"

%% Translation of GIT committish: 6977ddc9a3b63ea810eaecb864269c7d847ccf98
  texidoces = "

Se pueden imprimir los números de compás a intervalos regulares
mediante el establecimiento de la propiedad
@code{barNumberVisibility}.  Aquí los números de compás se
imprimen a cada dos compases excepto al final de la línea.

"

  doctitlees = "Imprimir números de compás a intervalos regulares"



%% Translation of GIT committish: 0a868be38a775ecb1ef935b079000cebbc64de40
  texidocde = "
Taktnummern können in regelmäßigen Intervallen gesetzt werden, indem
man die Eigenschaft @code{barNumberVisibility} definiert.  In diesem
Beispiel werden die Taktnummern jeden zweiten Takt gesetzt, außer
am Ende einer Zeile.

"
  doctitlede = "Setzen der Taktnummern in regelmäßigen Intervallen"



%% Translation of GIT committish: 374d57cf9b68ddf32a95409ce08ba75816900f6b
  texidocfr = "
Vous pouvez imprimer un numéro de mesure à intervalle régulier plutôt
qu'en tête de chaque ligne seulement, en recourant à la propriété
@code{barNumberVisibility}.  Voici comment afficher le numéro toutes les
deux mesures sauf en fin de ligne.

"
  doctitlefr = "Imprimer les numéros de mesure à intervalle régulier"

  texidoc = "
Bar numbers can be printed at regular intervals by setting the property
@code{barNumberVisibility}. Here the bar numbers are printed every two
measures except at the end of the line.

"
  doctitle = "Printing bar numbers at regular intervals"
} % begin verbatim

\relative c' {
  \override Score.BarNumber #'break-visibility = #end-of-line-invisible
  \set Score.currentBarNumber = #11
  % Permit first bar number to be printed
  \bar ""
  % Print a bar number every second measure
  \set Score.barNumberVisibility = #(every-nth-bar-number-visible 2)
  c1 | c | c | c | c
  \break
  c1 | c | c | c | c
}

