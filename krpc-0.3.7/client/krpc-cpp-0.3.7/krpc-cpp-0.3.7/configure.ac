AC_INIT([krpc], [0.3.7])
AC_SUBST([LT_RELEASE],[0.3.7])
AM_INIT_AUTOMAKE
AC_CONFIG_MACRO_DIR(m4)
AC_PROG_CXX
AC_LANG([C++])
AX_CXX_COMPILE_STDCXX_11(noext, mandatory)
AC_PROG_LIBTOOL
AC_CHECK_HEADER(google/protobuf/message.h, , AC_MSG_ERROR([Couldn't find protobuf headers."]))
AC_CHECK_HEADER(asio.hpp, , AC_MSG_ERROR([Couldn't find ASIO headers. Try "sudo apt-get install libasio-dev"]))
AC_OUTPUT(Makefile include/Makefile src/Makefile)
