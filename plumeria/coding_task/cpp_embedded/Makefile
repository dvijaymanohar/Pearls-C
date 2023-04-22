SRCS=task_test.cpp
HDRS=task.h

PROGRAM=interview

CXXFLAGS += -std=c++11 -DDEBUG -D_GLIBCXX_DEBUG -O0 -g
LDFLAGS += -lm

all: $(PROGRAM)
	./$(PROGRAM)

clean:
	-rm $(PROGRAM)

$(PROGRAM) : $(SRCS) $(HDRS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(SRCS) -o $@
