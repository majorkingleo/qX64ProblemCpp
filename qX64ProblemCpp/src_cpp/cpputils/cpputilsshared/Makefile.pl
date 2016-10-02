
# it is required to install  to the prod directory

if( $ENV{SRCDIR} || $ENV{EXTERNAL_CPPUTILS} ) {

&Rulemore('install', 'HEADERFILES', '',
        "\@mkdir -p \$($standard::ENVROOTDIR)/include && cp -f *.h \$($standard::ENVROOTDIR)/include");

&Rulemore('install', 'LIBS', '',
        "\@mkdir -p \$($standard::ENVROOTDIR)/lib && cp -f \$(LIBRARY) \$($standard::ENVROOTDIR)/lib");

}		

$eof;
