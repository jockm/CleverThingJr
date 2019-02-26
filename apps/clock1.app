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
	var m = get(95)
	var d = get(94)
	var y = 2000 + get(96)

	# put the month in string 18
	strset(18, m)

	# Add a space
	str " "
	strcat(18, 0)

	# Add a 2 digit date 
	pad(0, d, 2, 48)
	strcat(18, 0)

	# Add the year
	str " ", y
	strcat(18, 0)

	var x = 128 - (strlen(18) * 8)
	draw(x / 2, 12, 18)
}

func displayDateTime() {
	displayTime()
	displayDate()
}


func clearMessageArea() {
	fg(bgColor)
	frect(0, 54, 127, 20)
	fg(fgColor)
}


func onTick() {
	gettime(90)
	
	if(get(90) = 0) {
		displayDateTime()
	}
}



func onAction(a, b) {
	if(a) {
		clearMessageArea()
	}
}

func onMessage() {
	clearMessageArea()

	var x = 128 - (strlen(20) * 8)
	var X = 128 - (strlen(21) * 8)

	if(x < 0) {
		x = 0
	}

	if(X < 0) {
		X = 0
	}

	draw(x / 2, 54, 20);
	draw(X / 2, 64, 21);
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

	gettime(90)
	displayDateTime()
}