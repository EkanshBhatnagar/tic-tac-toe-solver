# All Target
all: tic-tac-toe-solver

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../AiPlayer.cpp \
../Game.cpp \
../GameBoard.cpp \
../Heuristic.cpp \
../HumanPlayer.cpp \
../Move.cpp \
../Node.cpp \
../Player.cpp \
../TicTacToeProgram.cpp 

OBJS += \
./AiPlayer.o \
./Game.o \
./GameBoard.o \
./Heuristic.o \
./HumanPlayer.o \
./Move.o \
./Node.o \
./Player.o \
./TicTacToeProgram.o 

CPP_DEPS += \
./AiPlayer.d \
./Game.d \
./GameBoard.d \
./Heuristic.d \
./HumanPlayer.d \
./Move.d \
./Node.d \
./Player.d \
./TicTacToeProgram.d 

%.o: %.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++14 -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

tic-tac-toe-solver: $(OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GCC C++ Linker'
	g++ -std=c++14 -o "tic-tac-toe-solver" $(OBJS)
	@echo 'Finished building target: $@'
	@echo ' '

clean:
	rm $(OBJS) $(CPP_DEPS) tic-tac-toe-solver
	-@echo ' '
