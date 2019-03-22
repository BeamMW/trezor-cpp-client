CXX       = g++

OPTFLAGS = -O3 -g3

LDLIBS = -lcurl

CXXFLAGS   += $(OPTFLAGS) \
            -pedantic \
            -Wall \
            -Wextra \
            -Wcast-align \
            -Wcast-qual \
            -Wctor-dtor-privacy \
            -Wdisabled-optimization \
            -Wformat=2 \
            -Winit-self \
            -Wlogical-op \
            -Wmissing-declarations \
            -Wmissing-include-dirs \
            -Wnoexcept \
            -Wold-style-cast \
            -Woverloaded-virtual \
            -Wredundant-decls \
            -Wshadow \
            -Wsign-conversion \
            -Wsign-promo \
            -Wstrict-null-sentinel \
            -Wstrict-overflow=5 \
            -Wswitch-default \
            -Wundef \
            -Wno-unused \
            # -Werror

CXXFLAGS += -I.

SRCS   = main.cpp

OBJS   = $(SRCS:.cpp=.o)

%.o: %.c %.h
	$(CXX) $(CXXFLAGS) -o $@ -c $<

main: $(OBJS)
	$(CXX) -o main $(OBJS) $(LDLIBS) 

clean:
	rm -f *.o
	rm -f main
