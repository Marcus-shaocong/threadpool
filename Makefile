#############################################################################
#
# #  Makefile for assignment 1
#  #
#############################################################################

CXX			= g++
CFILES      = main.cxx basic_thread.cxx basic_thread.hxx rep_thread.cxx rep_thread.hxx rep_thread.cxx rep_thread_pool.cxx rep_thread_pool.hxx
DEPS		= basic_thread.hxx rep_thread.hxx rep_thread_pool.hxx
OFILES		= main.o thread.o
CFLAGS      = -pthread

thread.o : main.cxx basic_thread.cxx basic_thread.hxx rep_thread.cxx rep_thread.hxx rep_thread.cxx rep_thread_pool.cxx rep_thread_pool.hxx 
	$(CXX) -c -o $@ $< $(CFLAGS)

main.o : main.cxx basic_thread.cxx basic_thread.hxx rep_thread.cxx rep_thread.hxx rep_thread.cxx rep_thread_pool.cxx rep_thread_pool.hxx 
	$(CXX) -c -o $@ $< $(CFLAGS)

#main: $(OFILES)
#      $(CXX) -o $@ $^ $(CFLAGS) 

