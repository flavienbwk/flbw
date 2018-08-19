#!/usr/bin/env perl

# Will generate a ~1Mo string of Lorem Ipsum for benchmark test.
# Capture it with "./text_generator.sh > big.txt" to save it in a file.
# apt-get install libtext-lorem-perl -y

use Text::Lorem;

my $text = Text::Lorem->new();
$paragraphs = $text->paragraphs(5000);

print $paragraphs;
