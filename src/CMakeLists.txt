add_sources(main.cpp)

# git
add_sources(
  git/error.h
  git/misc.h
  git/oid.h
  git/repository.h
  git/revwalk.h)
add_sources(
  git/error.cpp
  git/oid.cpp
  git/repository.cpp
  git/revwalk.cpp)

# bl
add_sources(bl/preferences.h)
add_sources(bl/preferences.cpp)

# ui
add_sources(ui/ui.qrc)
