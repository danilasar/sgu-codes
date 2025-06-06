#import "@preview/bubble:0.2.2": *

#show: bubble.with(
  title: "Анализы",
  subtitle: "сложности алгоритмов",
  author: "Данила Григорьев",
  affiliation: "Саратовский государственный университет",
  date: datetime.today().display(),
  year: "2025",
  class: "251 группа",
  other: (),
  logo: "",
  color-words: ("important",)
) 

#include "labs/strings1.typ"
#include "labs/strings2.typ"
#include "labs/binary_tree.typ"
#include "labs/rb_tree.typ"
#include "labs/avl_tree.typ"
#include "labs/boyer_moore.typ"
#include "labs/prefix_z_kmp.typ"

