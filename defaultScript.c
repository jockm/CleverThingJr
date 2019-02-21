/*
 * defaultScript.c
 *
 *  Created on: Feb 18, 2019
 *      Author: jock
 */
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

