/*
 * defaultScript.c
 *
 *  Created on: Feb 18, 2019
 *      Author: jock
 */
#if 1
const char *defaultScript = R"(
var fgColor = 0xFFFF
var bgColor = 255

func displayTime() {
	var am = 1;

	if(get(92) >= 12) {
		am = 0
	}

	if(get(92) >= 13) {
		set(92, get(92) - 12)
	}
	
	pad(18, get(92), 2, 48);
	pad(19, get(91), 2, 48);

	strccat(18, 58)
	strcat(18, 19)

	if(am) {
		str " AM"
	} else {
		str " PM"
	}

	strcat(18, 0)
	
	var x = 128 - (strlen(18) * 8)

	draw(x / 2, 2, 18)
}


func displayDate() {
	print "Duck displayDate alt"
	var m = get(95)
	var d = get(94)
	var y = 2000 + get(96)

	print "Duck displayDate alt 1"
	# put the month in string 18
	strset(18, m)

	print "Duck displayDate alt 2"
	# Add a space
	str " "
	strcat(18, 0)

	print "Duck displayDate alt 3"
	# Add a 2 digit date 
	pad(0, d, 2, 48)
	strcat(18, 0)

	print "Duck displayDate alt 4"
	# Add the year
	str " ", y
	strcat(18, 0)

	print "Duck displayDate alt 4"
	var x = 128 - (strlen(18) * 8)
	draw(x / 2, 12, 18)

	str get(90), " ", get(91), " ", get(92), " ", get(93), " ", get(94), " ", get(95), " ", get(96)
	strset(18, 0) 
	var x = 128 - (strlen(18) * 8)
	draw(x / 2, 20, 18)

	print "Duck displayDate alt end"
}

func displayDateTime() {
	print "Duck displayDateTime 1"
	displayTime()
	print "Duck displayDateTime 2"
	displayDate()
	print "Duck displayDateTime 3"
}

func onTick() {
	gettime(90)
	
	if(get(90) = 0) {
		#displayDateTime()
	}
}


func appletInit() {
	fg(fgColor)
	bg(bgColor)
	cls(bgColor)

	########
	# Build UI
	str "Clear"
	draw(0, 119, 0)

	hline(0, 21, 127)
	hline(0, 116, 127)
	print "Duck 1"

	########
	# Month List
	str "Jan"
	strset(1, 0)

	str "Feb"
	strset(2, 0)

	str "Mar"
	strset(3, 0)

	str "Apr"
	strset(4, 0)

	str "May"
	strset(5, 0)

	str "Jun"
	strset(6, 0)

	str "Jul"
	strset(7, 0)

	str "Aug"
	strset(8, 0)

	str "Sep"
	strset(9, 0)

	str "Oct"
	strset(10, 0)

	str "Nov"
	strset(11, 0)

	str "Dec"
	strset(12, 0)

print "Duck 2"
	gettime(90)
print "Duck 3"
	displayDateTime()
print "Duck 4"
}
)";
#else
const char *defaultScript = R"(
var fgColor = 0xFFFF
var bgColor = 255

var currApp = 0

func displayTime() {
	var am = 1;

	fg(bgColor)
	frect(0, 0, 128, 10)
	fg(fgColor)
	
	gettime(10)

	if(get(12) >= 12) {
		am = 0
	}

	if(get(12) >= 13) {
		set(12, get(12) - 12)
	}
	
	pad(18, get(12), 2, 48);
	pad(19, get(11), 2, 48);

	strccat(18, 58)
	strcat(18, 19)

	if(am) {
		str " AM"
	} else {
		str " PM"
	}

	strcat(18, 0)
	
	sprint(18)

	var x = 128 - (strlen(18) * 8)

	draw(x / 2, 4, 18)
}

func onTick() {
	gettime(10)
	
	if(get(10) = 0) {
		displayTime()
	}
}


func onMessage() {
}


func onAction(a, b) {
	if(a) {
		hilight(currApp, 0)
		currApp = currApp + 1;
	
		if(currApp >= get(0)) {
			currApp = 0
		}

		hilight(currApp, 1)
	}

	if(b) {
		SYSLOAD(currApp + 1)
	}
}


func hilight(idx, show) {
	if(show) {
		str ">"
	} else {
		str " "
	}

	draw(1, 18 + idx * 9, 0)	
}


func appletInit() {
	fg(fgColor)
	bg(bgColor)
	cls(bgColor)
	
	str "Next        Set!"
	draw(0, 119, 0)

	hline(0, 13, 127)
	hline(0, 117, 127)

	displayTime()

	if(get(0) = 0) {
		str "No Apps Found"
		draw(15, 60, 0)
		return
	}

	var idx = 0;
	while(idx < get(0)) {
		draw(10, 18 + idx * 9, idx + 1)
		idx = idx + 1
	}

	hilight(currApp, 1)
}
)";
#endif

