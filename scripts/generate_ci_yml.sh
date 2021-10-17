#!/bin/sh

ls ../tests/ | xargs -I FOO sh -c 'sed -r "s/NAME/FOO/g" github-test-template.yml' >> ../.github/workflows/ci.yml
