# **************************************************************************** #
#                                                                              #
#                                   IRC                                        #
#                                                                              #
# **************************************************************************** #

TARGET = ircserv

CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98

SRCS_PATH	:=	src/
SRCS := $(SRCS_PATH)main.cpp \
		$(SRCS_PATH)ft_irc.cpp

INCL_PATH	:=	include/
INCL		:=	-I $(INCL_PATH)
# HEADERS :=  include/main.hpp \
# 			include/Network.hpp

OBJS = $(patsubst %.cpp, bin/%.o,$(SRCS))

# **************************************************************************** #

all: $(TARGET)

bin/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(INCL)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET) $(CXXFLAGS)

clean:
	rm -rf bin

fclean: clean
	rm -f $(TARGET)

re: fclean all
