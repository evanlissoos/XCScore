#!/bin/bash

cd src/ \
&& make \
&& mv xcscore ../ \
&& make clean
