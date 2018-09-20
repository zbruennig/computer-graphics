# computer-graphics

For source control, I have used a private Github repo.<br>
It requires a README. Here it is.

### FAQ

##### Why did you change the Makefile, Zach?

I have added two commands to the Makefile to help with development,<br>
`make clean` and `make again`. Beyond that, I have made no other changes to the Makefile.

##### So, you went and made a Github repo for this. Isn't that against EECS policy maybe?

Yes, that was a thing back in EECS168/268 wasn't it? Well the good news is<br>
the repository I am committing and pushing to is private - only I am<br>
able to grant people access. If anyone is concerned about sharing code,<br>
that would be impossible to accomplish without my express knowledge.

Additionally, I have found nothing in the syllabus which would forbid<br>
me from doing this. However, at the request of the course instructor or<br>
any EECS administrator I would be happy to remove this project from Github.

##### What changes were made from the template?

Check the revision history.

##### How do I run this?

First compile it with `make`. This compiles fine for me on the Linux EECS machines.<br>
I have provided the two given sample files in this repo. They can be tested with<br>
`./main samples/iris.txt` and `./main samples/AndrewsTable1.txt`

##### Were any files outside this directory modified?

The only changes from the template are included in this repository.<br>
The controllers and shader interface are untouched.

##### You do this really weird thing where your style changes with pretty much every other line. Why is that?

So this is a really minor point but thanks for bringing it up because it annoys me too.<br>
The biggest differences you will probably find with my style is my spacing in<br>
`for`, `if/else`, and `while` blocks. Throughout most of my coding life I have been<br>
a large fan of not leaving any whitespace between brackets, keywords, and operators.<br>
However at a recent internship the code base I was working on required me to use a<br>
custom linter, which forced many stylistic choices on me including adding whitespace<br>
in several places. Another noticeable difference would be my affinity for ternary<br>
operators. In place of a conditional assignment if block<br>
`(if some condition then variable = something)` I will often choose to write it in a<br>
format akin to `variable = condition ? something : itself`. This is in large part<br>
due to spending a lot of time in Ruby, where conditional assignments are common in<br>
that format, using the `if` and `unless` keywords. It's messed with my logic and<br>
as a direct consequence I immediately try to style my code in that way.

##### Don't you figure this readme is getting a bit too long for something MAYBE one person will read?

Good point. I'll stop.
