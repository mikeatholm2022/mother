

CXX = g++

DEBUG = 0

APP_NAME=mother

#INC_DIRS = -I"." -I"/opt/boost/include" -I"src" -I"utils"
INC_DIRS = -I"$(BOOST_ROOT)/include" -I"$(CHAOS_ROOT)/base" -I"$(CHAOS_ROOT)/application"
LIB_DIRS = -L"$(BOOST_ROOT)/lib" -L"$(CHAOS_ROOT)/bin"


# By default lets just build DEBUG
CXXFLAGS = -O0 -ggdb3 -fPIC -std=c++20 -DBOOST_BIND_GLOBAL_PLACEHOLDERS


VERSION=v1.0.0
#VERSION = $(shell git describe --abbrev=8 --dirty --always --tags)


#ifeq ($(DEBUG),1)
#   CXXFLAGS = -O0 -ggdb3 -fPIC -std=c++20
#else
#   CXXFLAGS = -O3 -pthread -fPIC -fomit-frame-pointer -march=native -Wno-write-strings -ffloat-store -ffast-math -fno-math-errno -std=c++20 -DVERSION=\"$(VERSION)\"
#endif

# For speed
#CXXFLAGS = -O3 -pthread -ffast-math -ffloat-store -fPIC
#CXXFLAGS = -O3 -pthread -fPIC
# Not currently supported -flto -fmudflapir -fmudflapth
# For debugging with the most verbose errors and warnings
#CXXFLAGS = -O0 -pthread -g -fPIC -Wall

LDFLAGS = -pthread -lrt -ldl -lz -lboost_system -lboost_thread -lboost_filesystem -lboost_date_time -luuid -lchaos_base


# Use this for multiple directories
csrc =	$(wildcard src/*.cpp)
obj = 	$(csrc:.cpp=.o)
dep = 	$(wildcard src/*.h)
deps =	$(dep:.h=.d)

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INC_DIRS) $< -o $@

../bin/$(APP_NAME): $(obj)
	$(CXX) $(LIB_DIRS) -o $@ $^ $(LDFLAGS)
#	$(CXX) $(LIBPATH) -Wl,-rpath,../lib -o $@ $^ $(LDFLAGS)

-include $(deps)
%.d: %.cpp
		@$(CXX) $(CXXFLAGS) $(INC_DIRS) $< -MM -MT $(@:.d=.o) >$@


.PHONY: clean
clean:
		rm -f ../bin/$(APP_NAME) $(obj)

.PHONY: cleandep
cleandep:
		rm -f $(deps)

.PHONY: cleanall
cleanall:
		rm -f ../bin/$(APP_NAME) $(obj)
		rm -f $(deps)





