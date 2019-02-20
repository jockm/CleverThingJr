var fgColor = 0xFFFF
var bgColor = 255

var currLine = 0

func displayTime() {
	var am = 1;

	#fg(bgColor)
	#frect(0, 0, 128, 10)
	#fg(fgColor)
	
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
	
	sprint(18)

	var x = 128 - (strlen(18) * 8)

	draw(x / 2, 2, 18)
}

func onTick() {
	gettime(90)
	
	if(get(90) = 0) {
		displayTime()
	}
}


func onMessage() {
}


func onAction(a, b) {
	if(a) {
		hilight(currLine, 0)
		currLine = currLine + 1;
	
		if(currLine >= 8) {
			currLine = 0
		}

		hilight(currLine, 1)
	}

	if(b) {
		if(currLine < 7) {
			updateValue(currLine)
		} else {
			updateTime()
		}
	}
}


func hilight(idx, show) {
	if(show) {
		str ">"
	} else {
		str " "
	}

	draw(1, get(10 + idx), 0)	
}


func updateTime() {
	set(82, get(0)) # Hour
	set(81, get(1)) # Minute
	set(80, get(2)) # Second
	set(83, get(3)) # Day
	set(84, get(4)) # Date
	set(85, get(5)) # Month
	set(86, get(6)) # Year

	settime(80)
	gettime(90)
	displayTime()
}


func updateValue(idx) {
	var v = get(idx) + 1

	if(v > get(30 + idx)) {
		v = get(20 + idx)
	}

	set(idx, v)
	showValue(idx)
}


func showValue(idx) {
	if(idx = 3) {
		strset(0, get(idx))
	} else {
		str get(idx), "   "
	}

	draw(60, get(10 + idx), 0)
}


func appletInit() {
	fg(fgColor)
	bg(bgColor)
	cls(bgColor)

	#################
	# List of Y addresses for each setting
	set(10, 16 + 0 * 9) # Hour
	set(11, 16 + 1 * 9) # Minute
	set(12, 16 + 2 * 9) # Second

	set(13, 16 + 4 * 9) # Day of the Week

	set(14, 16 + 6 * 9) # Date
	set(15, 16 + 7 * 9) # Month
	set(16, 16 + 8 * 9) # Year
	
	set(17, 18 + 10 * 9) # Set!
	
	#################
	# List of min values for each setting
	set(20, 0) # Hour
	set(21, 0) # Minute
	set(22, 0) # Second

	set(23, 1) # Day of the Week

	set(24, 1) # Date
	set(25, 1) # Month
	set(26, 0) # Year

	set(27, 0) # Set!

	#################
	# List of max values for each setting
	set(30, 23) # Hour
	set(31, 59) # Minute
	set(32, 59) # Second

	set(33, 7) # Day of the Week

	set(34, 31) # Date
	set(35, 11) # Month
	set(36, 99) # Year

	set(37, 0) # Set!
	
	#################
	# List of names for each day of the week
	str "Sun"
	strset(1, 0)

	str "Mon"
	strset(2, 0)

	str "Tue"
	strset(3, 0)

	str "Wed"
	strset(4, 0)

	str "Thu"
	strset(5, 0)

	str "Fri"
	strset(6, 0)

	str "Sat"
	strset(7, 0)


	#################
	# List of names for each setting
	str "Hour"
	strset(10, 0)
	
	str "Min"
	strset(11, 0)
	
	str "Sec"
	strset(12, 0)
	
	str "Day"
	strset(13, 0)
	
	str "Date"
	strset(14, 0)
	
	str "Month"
	strset(15, 0)
	
	str "Year"
	strset(16, 0)
	
	str "Set!"
	strset(17, 0)
	

	#################
	# Load the time
	gettime(90)
	
	set(0, get(92)) # Hour
	set(1, get(91)) # Minute
	#set(2, get(90)) # Second
	set(2, 0) # Second
	set(3, get(93)) # Day
	set(4, get(94)) # Date
	set(5, get(95)) # Month
	set(6, get(96)) # Year

	# Sanity Check
	if(get(3) < 1) {
		set(3, 1)
	}

	if(get(5) < 1) {
		set(5, 1)
	}
	
	#################
	# Draw the UI
	str "Next           +"
	draw(0, 119, 0)

	hline(0, 11, 127)
	hline(0, 116, 127)

	displayTime()
	
	var idx = 0
	while(idx < 8) {
		draw(10, get(10 + idx), 10 + idx)

		if(idx < 7) {
			showValue(idx)
		}

		idx = idx + 1
	}
	
	hilight(currLine, 1)
}
