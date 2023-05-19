#!/bin/bash

# Generate output
mkdir -p output
models=(tiny base small medium large)
audios=$(ls audio/*.wav)

for audio in $audios
do
    for model in ${models[@]}
    do
        name=$(echo ${audio} | sed -E 's/.*\/(.*).wav/\1/')
        whisper $audio --model $model > output/$name-$model.out
    done
done