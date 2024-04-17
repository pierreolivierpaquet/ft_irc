# **************************************************************************** #
#                                                                              #
#                                   IRC                                        #
#                                                                              #
# **************************************************************************** #

TARGET		:=	ircserv

CXX			:=	c++
CXXFLAGS	:=	-Wall -Wextra -Werror -std=c++98

SRCS_PATH	:=	src/
CMD_PATH	:=	cmd/
SRCS		:=	$(SRCS_PATH)main.cpp						\
				$(SRCS_PATH)Clients.cpp						\
				$(SRCS_PATH)Server.cpp						\
				$(SRCS_PATH)Channel.cpp						\
				$(SRCS_PATH)parsing.cpp						\
				$(SRCS_PATH)Commands.cpp 					\
				\
				$(SRCS_PATH)$(CMD_PATH)cmd_pass.cpp			\
				$(SRCS_PATH)$(CMD_PATH)cmd_user.cpp			\
				$(SRCS_PATH)$(CMD_PATH)cmd_nick.cpp			\
				$(SRCS_PATH)$(CMD_PATH)cmd_invite.cpp		\
				$(SRCS_PATH)$(CMD_PATH)cmd_kick.cpp			\
				$(SRCS_PATH)$(CMD_PATH)cmd_topic.cpp		\
				$(SRCS_PATH)$(CMD_PATH)cmd_channel.cpp		\
				$(SRCS_PATH)$(CMD_PATH)cmd_privatemsg.cpp	\
				$(SRCS_PATH)$(CMD_PATH)cmd_part.cpp			\
				$(SRCS_PATH)$(CMD_PATH)cmd_mode.cpp			\
				$(SRCS_PATH)$(CMD_PATH)cmd_quit.cpp			\

INCL_PATH	:=	include/
INCL		:=	-I $(INCL_PATH)

OBJS		:=	$(patsubst %.cpp, bin/%.o,$(SRCS))
BIN_PATH	:=	bin/
DEL			:=	rm -rf

# ------------------------------------------------------------ @category COLOR.S
ESC_SEQ				:=		\033[#		ESCAPE SEQUENCE CHARACTER
C_RST				:=		$(ESC_SEQ)0m#		RESETS COLOR.S
C_BLD				:=		$(ESC_SEQ)1m#		BOLD
C_RED				:=		$(ESC_SEQ)31m#			RED
C_B_RED				:=		$(ESC_SEQ)1;31m#		BOLD RED
C_GRN				:=		$(ESC_SEQ)32m#			GREEN
C_B_GRN				:=		$(ESC_SEQ)1;32m#		BOLD GREEN
C_ORN				:=		$(ESC_SEQ)38;5;208m#	ORANGE
C_B_ORN				:=		$(ESC_SEQ)1;38;5;208m#	BOLD ORANGE
C_B_YEL				:=		$(ESC_SEQ)1;33m#		BOLD YELLOW

# -------------------------------------------------------------- @category STYLE
STAB	:=	\t
DTAB	:=	$(STAB)$(STAB)
TTAB	:=	$(STAB)$(DTAB)
UP		:=	$(ESC_SEQ)1A
CUT		:=	$(ESC_SEQ)K
UPCUT	:=	$(UP)$(CUT)

OK_BOX		:=	[$(C_B_GRN)  OK  $(C_RST)]
KO_BOX		:=	[$(C_B_RED)  KO  $(C_RST)]
BUILD_BOX	:=	[$(C_B_ORN)  .o  $(C_RST)]
EXEC_BOX	:=	[$(C_B_YEL)  ./  $(C_RST)]

# **************************************************************************** #

all: $(TARGET)

$(BIN_PATH)%.o: %.cpp
	@mkdir -p $(@D)
	@	echo	"$(STAB)$(BUILD_BOX)$(C_B_ORN)"								\
				"Building $@ from $<$(C_RST)";
	@$(CXX) $(CXXFLAGS) -c $< -o $@ $(INCL)

$(TARGET): $(OBJS)

	@if [ ! -f $(TARGET) ];													\
	then																	\
		echo	"$(STAB)$(EXEC_BOX)"										\
				"$(C_B_YEL)Compiling \`$@\`...$(C_RST)";					\
	fi;

	@$(CXX) $(OBJS) -o $(TARGET) $(CXXFLAGS)
	@	if	[ -f $(TARGET) ];												\
		then																\
			echo	"$(STAB)$(OK_BOX)"										\
					"$(C_B_GRN)./$(TARGET) executable ready!$(C_RST)";		\
		else																\
			echo	"$(STAB)$(KO_BOX) something happened: try again.";		\
		fi;

clean:
	@	if	[ -d $(BIN_PATH) ]; then										\
			$(DEL) $(BIN_PATH);												\
			echo	"$(STAB)$(OK_BOX)$(C_B_GRN)"							\
					"$(BIN_PATH) directory deleted.$(C_RST)";				\
		else																\
			echo	"$(STAB)$(KO_BOX)$(C_B_RED)"							\
					"$(BIN_PATH) directory does not exists.$(C_RST)";		\
		fi;

fclean: clean
	@	if	[ -f $(TARGET) ]; then											\
			$(DEL) $(TARGET);												\
			echo "$(STAB)$(OK_BOX)$(C_B_GRN)"								\
			"\`$(TARGET)\` executable deleted.$(C_RST)";					\
		else																\
			echo "$(STAB)$(KO_BOX)$(C_B_RED)"								\
			"\`$(TARGET)\` executable does not exists.$(C_RST)";			\
		fi;

re: fclean all

ip:
	@ipconfig getifaddr en1

pdf:
	@open https://cdn.intra.42.fr/pdf/pdf/94732/fr.subject.pdf

intra:
	@open https://projects.intra.42.fr/projects/ft_irc

debug:	CXX += -g
debug:	CXX += -Wno-unused-variable -Wno-unused-function
debug:	CXX += -Wno-unused-parameter -Wno-unused-const-variable
debug:	CXX += -Wno-unused-private-field
debug:	fclean $(OBJS) $(TARGET)

PASSWORD := toto
PORT := 6667
run: $(TARGET)
	@echo "MAKE RUN\t"
	./$(TARGET) $(PORT) $(PASSWORD)

.PHONY: all $(TARGET) clean fclean re
