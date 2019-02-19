/*
 * defaultScript.c
 *
 *  Created on: Feb 18, 2019
 *      Author: jock
 */
const char *defaultScript = R"(
var fgColor = 0xFFFF
var bgColor = 255

func displayTime() {
	fg(bgColor)
	frect(0, 10, 128, 8)
	fg(fgColor)
	
	time(10)
	print get(12), ":", get(11)
	str get(12), ":",  get(11)

	draw(0, 10, 0)
}

func onTick() {
	print "Duck onTick"
	time(10)
	print get(12), ":", get(11), ".", get(10)
	
	if(get(10) = 0) {
		displayTime()
	}
}


func onMessage() {
}


func onAction(a, b) {
}


func appletInit() {
	print "Duck appletInit"

	fg(fgColor)
	bg(bgColor)
	cls(bgColor)
	
	displayTime()
}
)";

