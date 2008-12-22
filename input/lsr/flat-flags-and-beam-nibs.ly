%% Do not edit this file; it is auto-generated from LSR http://lsr.dsi.unimi.it
%% This file is in the public domain.
\version "2.11.66"

\header {
  lsrtags = "rhythms"

  texidoces = "
 Son posibles tanto los corchetes rectos sobre notas sueltas como
extremos de barra sueltos en figuras unidas, con una combinación de
@code{stemLeftBeamCount}, @code{stemRightBeamCount} e indicadores de
barra @code{[ ]} emparejados.




Para corchetes rectos que apunten a la derecha sobre notas sueltas,
use indicadores de barra emparejados @code{[ ]} y establezca
@code{stemLeftBeamCount} a cero (véase el ejemplo 1).




Para corchetes rectos que apunten a la izquierda, establezca en su
lugar @code{stemRightBeamCount} (ejemplo 2).




Para extremos sueltos que apunten a la derecha al final de un conjunto
de notas unidas, establezca @code{stemRightBeamCount} a un valor
positivo.  Y para extremos sueltos que apunten a la izquierda al
principio de un conjunto de notas unidas, establezca
@code{stemLeftBeamCount} en su lugar (ejemplo 3).




A veces, para una nota suelta rodeada de silencios tiene sentido que
lleve los dos extremos sueltos del corchete plano, apuntando a derecha
e izquierda.  Hágalo solamente con indicadores de barra emparejados
@code{[ ]} (ejemplo 4).




(Observe que @code{\\set stemLeftBeamCount} siempre equivale a
@code{\\once \\set}.  En otras palabras, los ajustes de la cantidad de
barras no se recuerdan, y por ello el par de corchetes planos
aplicados a la nota Do semicorchea @code{c'16 [ ]} del último ejemplo
no tiene nada que ver con el @code{\\set} de dos notas por detrás.)




"
  doctitlees = "Corchetes rectos y extremos de barra sueltos"

  texidoc = "
 Flat flags on lone notes and beam nibs at the ends of beamed figures
are both possible with a combination of @code{stemLeftBeamCount}, 
@code{stemRightBeamCount} and paired @code{[ ]} beam indicators.




For right-pointing flat flags on lone notes, use paired @code{[ ]} beam
indicators and set @code{stemLeftBeamCount} to zero (see Example 1).




For left-pointing flat flags, set @code{stemRightBeamCount} instead
(Example 2).




For right-pointing nibs at the end of a run of beamed notes, set
@code{stemRightBeamCount} to a positive value. And for left-pointing
nibs at the start of a run of beamed notes, set
@code{stemLeftBeamCount} instead (Example 3).




Sometimes it may make sense for a lone note surrounded by rests to
carry both a left- and right-pointing flat flag. Do this with paired
@code{[ ]} beam indicators alone (Example 4).  




(Note that @code{\\set stemLeftBeamCount}is always equivalent to 
@code{\\once \\set}.  In other words, the beam count settings aren't 
\"sticky\", so the pair of flat flags attached to the lone  @code{c'16
[ ]} in the last example have nothing to do with the  @code{\\set} two
notes prior.)




"
  doctitle = "Flat flags and beam nibs"
} % begin verbatim

\score {
<<
% Example 1
\new RhythmicStaff {
  \set stemLeftBeamCount = #0
  c'16 [ ]
  r8.
}

% Example 2
\new RhythmicStaff {
  r8.
  \set stemRightBeamCount = #0
  c'16 [ ]
}

% Example 3
\new RhythmicStaff {
  c'16
  c'16
  \set stemRightBeamCount = #2
  c'16
  r16
  r16
  \set stemLeftBeamCount = #2
  c'16
  c'16
  c'16
}

% Example 4
\new RhythmicStaff {
   c'16
   c'16
   \set stemRightBeamCount = #2
   c'16
   r16
   c'16 [ ]
   r16
   \set stemLeftBeamCount = #2
   c'16
   c'16
}
>>
}
