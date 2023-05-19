all: setup build analysis

setup:
	sudo apt update && sudo apt install ffmpeg # Change on non-debian-based distribution
	pip install git+https://github.com/openai/whisper.git
	pip install --upgrade --no-deps --force-reinstall git+https://github.com/openai/whisper.git
	pip install setuptools-rust
	pip install -r requirements.txt
build:
	bash gen.sh

analysis:
	python analysis.py
