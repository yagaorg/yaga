add_sources(main.cpp)

# git
add_sources(
  git/checkout.h
  git/diff.h
  git/error.h
  git/init.h
  git/oid.h
  git/remote.h
  git/repository.h
  git/revwalk.h
  git/types.h)
add_sources(
  git/checkout.cpp
  git/diff.cpp
  git/error.cpp
  git/oid.cpp
  git/remote.cpp
  git/repository.cpp
  git/revwalk.cpp)

# bl
add_sources(bl/preferences.h)
add_sources(bl/preferences.cpp)

# ui
add_sources(ui/ui.qrc)
