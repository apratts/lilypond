%% Do not edit this file; it is auto-generated from LSR http://lsr.dsi.unimi.it
%% This file is in the public domain.
\version "2.11.66"

\header {
  lsrtags = "vocal-music"

  texidoc = "
In a vocal piece where there are several (two,four or more) lines of
lyrics, and common lyrics for all voices at some point, these common
lyrics may be vertically centered regardingly, as shown in the
following example:

"
  doctitle = "Vertically centered common lyrics"
} % begin verbatim

\include "english.ly"
leftbrace = \markup { \override #'(font-encoding . fetaBraces) \lookup #"brace240" }
rightbrace = \markup { \rotate #180 \leftbrace }

dropLyrics =
{
    \override LyricText #'extra-offset = #'(0 . -5)
    \override LyricHyphen #'extra-offset = #'(0 . -5)
    \override LyricExtender #'extra-offset = #'(0 . -5)
}

raiseLyrics =
{
    \revert LyricText #'extra-offset
    \revert LyricHyphen #'extra-offset
    \revert LyricExtender #'extra-offset
}

skipFour = \repeat unfold 4 { \skip 8 }

lyricsA = \lyricmode { The first verse has \dropLyrics the com -- mon
__ words \raiseLyrics used in all four. }
lyricsB = \lyricmode { In stan -- za two, \skipFour al -- so ap -- pear. }
lyricsC = \lyricmode { By the third verse, \skipFour are get -- ting dull. }
lyricsD = \lyricmode { Last stan -- za, and \skipFour get used once more. }

melody = \relative c' { c4 d e f g f e8( e f) d4 c e d c }

\score
{
        <<
                \new Voice = m \melody
                \new Lyrics \lyricsto m \lyricsA
                \new Lyrics \lyricsto m \lyricsB
                \new Lyrics \lyricsto m \lyricsC
                \new Lyrics \lyricsto m \lyricsD
        >>
}
