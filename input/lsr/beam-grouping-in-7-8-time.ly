%% Do not edit this file; it is auto-generated from LSR http://lsr.dsi.unimi.it
%% This file is in the public domain.
\version "2.11.66"

\header {
  lsrtags = "rhythms"

  texidoces = "
No está especificada ninguna agrupación predeterminada automática
de las barras para el compás de 7/8, de forma que si se requieren
barras automáticas se debe especificar la forma de agrupamiento.
Por ejemplo, para agrupar todas las barras en la forma 2-3-2 en el
compás de 7/8, especificamos los finales de barra en 2/8 y 5/8:

"
  doctitlees = "Agrupamiento de las barras en el compás de 7/8"
  
%% Translation of GIT committish :<6ce7f350682dfa99af97929be1dec6b9f1cbc01a>
texidocde = "
Es gibt keine automatischen Balkengruppen für 7/8-Takte.  Wenn diese
Taktart benötigt wird, müssen die Gruppierungen definiert werden.  Um
beispielsweise alle Noten in 2/8-3/8-2/8 aufzuteilen, müssen Balkenenden
für 2/8 und 5/8 definiert werden:

"
  doctitlede = "Balkengruppen für 7/8-Takte"

  texidoc = "
There are no default automatic beam groupings specified for 7/8 time,
so if automatic beams are required the grouping must be specified.  For
example, to group all beams 2-3-2 in 7/8 time, specify beam endings at
2/8 and 5/8: 

"
  doctitle = "Beam grouping in 7/8 time"
} % begin verbatim

\relative c'' {
  \time 7/8
  % rhythm 2-3-2
  a8 a a a a a a
  #(override-auto-beam-setting '(end * * 7 8) 2 8)
  #(override-auto-beam-setting '(end * * 7 8) 5 8)
  a8 a a a a a a
}
