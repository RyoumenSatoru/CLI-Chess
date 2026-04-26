# ================================================================
#  Hey! Welcome to the CLI-Chess Makefile.
#
#  Just run `make` and you're good to go.
#  The binary lands at build/bin/chess when it's done.
#
#  Quick reference:
#    make          → build the game
#    make debug    → build with debug symbols (for when things break)
#    make run      → build and launch immediately
#    make clean    → nuke the build folder and start fresh
#    make help     → show this again
# ================================================================


# --- Toolchain ---------------------------------------------------
# Change this to clang++ if you prefer, everything else just works.
CXX      := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -Wpedantic


# --- Where things live -------------------------------------------
SRC_DIR  := src
OBJ_DIR  := build/obj
BIN_DIR  := build/bin
TARGET   := $(BIN_DIR)/chess


# --- Find all source files automatically -------------------------
# No need to list them by hand — any .cpp you add gets picked up.
SRCS     := $(shell find $(SRC_DIR) -name '*.cpp')
OBJS     := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))


# --- Make sure all headers are reachable -------------------------
# Covers src/, src/Pieces/, src/utils/ — the works.
INCDIRS  := $(shell find $(SRC_DIR) -type d)
INCLUDES := $(addprefix -I, $(INCDIRS))


# =================================================================
#  Targets you actually care about
# =================================================================

.DEFAULT_GOAL := all

# The usual entry point — optimised, no debug noise.
.PHONY: all
all: CXXFLAGS += -O2 -DNDEBUG
all: $(TARGET)
	@echo ""
	@echo "  All done! Run it with:  ./$(TARGET)"
	@echo ""

# Flip this on when you're chasing a bug.
# Turns off optimisation so the debugger shows real line numbers.
.PHONY: debug
debug: CXXFLAGS += -g -O0 -DDEBUG
debug: $(TARGET)
	@echo ""
	@echo "  Debug build ready. Good luck out there."
	@echo ""

# Build and immediately drop you into the game.
.PHONY: run
run: all
	@echo "  Starting CLI-Chess..."
	@echo ""
	@$(TARGET)

# Wipe everything compiled. Useful when something feels cursed.
.PHONY: clean
clean:
	@echo "  Sweeping up..."
	@rm -rf build/
	@echo "  Clean slate."

# In case you forget the commands (we all do).
.PHONY: help
help:
	@echo ""
	@echo "  CLI-Chess — available commands"
	@echo "  --------------------------------"
	@echo "  make          build the game (release)"
	@echo "  make debug    build with debug symbols"
	@echo "  make run      build and launch immediately"
	@echo "  make clean    delete all build output"
	@echo "  make help     show this message"
	@echo ""


# =================================================================
#  The machinery (you probably won't need to touch this)
# =================================================================

# Link everything together into the final binary.
$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	@echo "  Linking..."
	@$(CXX) $(CXXFLAGS) $^ -o $@

# Compile each source file.
# The build/obj/ tree mirrors src/ so nothing collides.
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	@echo "  Compiling $<"
	@$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Auto-generated dependency files.
# This is what makes recompilation work correctly when you edit a header.
DEPS := $(OBJS:.o=.d)
-include $(DEPS)

$(OBJ_DIR)/%.d: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	@$(CXX) $(CXXFLAGS) $(INCLUDES) -MM -MT '$(@:.d=.o)' $< -MF $@