#!/bin/sh

find ../tests/ -maxdepth 1 -type d | cut -d "/" -f 3 | xargs -I FOO sh -c 'sed -r "s/NAME/FOO/g" github-test-template.yml' >> ../.github/workflows/ci.yml
