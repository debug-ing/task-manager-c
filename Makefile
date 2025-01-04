APP_NAME := task_manager
SRC := task_manager.c
OUTPUT := $(APP_NAME)


build: $(SRC)
	@echo "Building the project..."
	gcc -o $(OUTPUT) $(SRC)

run: build
	@echo "Running the application..."
	./$(OUTPUT)

clean:
	@echo "Cleaning up..."
	rm $(OUTPUT)

help:
	@echo "Makefile targets:"
	@echo "  build   - Build the Go project"
	@echo "  run     - Build and run the project"
	@echo "  clean   - Remove build file"