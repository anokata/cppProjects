#!/usr/bin/env bash
 
clang-tidy \
	-fix \
	-fix-errors \
	-header-filter=.* \
	--checks=readability-braces-around-statements,misc-macro-parentheses \
	$1 \
	-- -I.
