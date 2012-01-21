SUBDIRS(
  exercise1
  exercise2
  exercise3
  exercise4
  exercise5
  exercise6
  exercise7
  exercise8
  exercise9
  exercise10
  exercise11
  exercise12
  exercise13
  exercise14
  exercise15
  exercise16
  exercise17
  exercise18
# exercise19
  exercise20
  exercise21
  exercise22
  exercise23
  exercise24
  exercise25
  exercise26
  exercise27
  exercise28
  exercise29
  exercise31
# exercise32
# exercise33
# exercise34
 )

IF(WIN32)
  IF(NOT BORLAND)
    IF(NOT CYGWIN)
      IF(NOT MINGW)
#       SUBDIRS(
#  exercise35
#         )
      ENDIF(NOT MINGW)
    ENDIF(NOT CYGWIN)
  ENDIF(NOT BORLAND)
ENDIF(WIN32)

