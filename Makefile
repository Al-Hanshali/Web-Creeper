maxlinks:= 100
pagelimit:= 100
threads:= 10

all_targets:= compile run clean

all: ${all_targets}


compile:
	@clear
	@echo "Compiling file..."
	g++ -std=c++14 main.cpp -o _creeper -lssl -lpthread -w

run:
	@echo "Running..."
	./_creeper $(maxlinks) $(pagelimit) $(threads)

clean:
	rm -r -f _creeper
	@echo "All cleaned."



