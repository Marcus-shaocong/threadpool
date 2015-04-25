#!/usr/bin/perl
use Fcntl qw(:flock);
my $a = shift;
print $a;
my $count = 1;
my $retVal = 0;
my $start_run = time();
my @friends;
my $newfriend;

print "Content-type: text/html\n\n";
$myfile = "friends.txt";
$newfriend = $a; 
print $newfriend;
open(MYFILE, ">$myfile") || die;
flock(MYFILE, 1);
while(<MYFILE>) {
    if (m/^$newfriend$/) {
        print "You are already on the list!\n";
        exit;
    }
}
close(MYFILE);
push(@friends, $newfriend);
open(MYFILE, "+< $myfile") || die;
flock(MYFILE, 2);
seek(MYFILE, 0, 0); truncate(MYFILE, 0);
print MYFILE @friends;
close(MYFILE);
print "You are in my list, $newfriend!\n";
exit;

#while($count < 100000000)
#{
#    if ( $count % 10000000 == 0 )
#    {   print "hello $count\n";
#    }
#    $count++;
#}
#my $end_run = time();
#my $run_time = $end_run - $start_run;
#print "Job took $run_time secondes\n";
#exit(0)

