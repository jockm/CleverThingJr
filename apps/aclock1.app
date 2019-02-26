var fgColor = 0xFFFF
var bgColor = 255

var hColor = 0xFFFF
var mColor = 0xFFFF

var minX = 0
var minY = 0
var hourX = 0
var hourY = 0

var marginX = 12
var marginY = 10

func displayTime() {
	var h = get(92)
	var m = get(91)
	var am = 1;
	var x = 0
	var y = 0
	var v = 0

	# Erase old lines
	fg(bgColor)
	line(49 + marginX, 49 + marginY, minX + marginX, minY + marginY)
	line(49 + marginX, 49 + marginY, hourX + marginX, hourY + marginY)
	

	# Get AM/PM and adjust hours to 0-11 

	if(h >= 11) {
		am = 0
		h = h - 12
	}

	# Draw the minutes line
	v = get(m) & 0xFFFF
	minY = v & 0xFF
	minX = v >> 8

	fg(mColor)
	line(49 + marginX, 49 + marginY, minX + marginX, minY + marginY)

	# Draw the hours line
	v = get(h) >> 16
	hourY = v & 0xFF
	hourX = v >> 8

	fg(hColor)
	line(49 + marginX, 49 + marginY, hourX + marginX, hourY + marginY)

	fg(fgColor)

	if(am) {
		str " AM"
	} else {
		str " PM"
	}

	draw(102, 0, 0)
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

	draw(0, 0, 18)
}

func displayDateTime() {
	displayTime()
	displayDate()
}


func clearMessageArea() {
	fg(bgColor)
	frect(0, 100 + marginY + 1, 127, 20)
	fg(fgColor)
}


func onTick() {
	print "Duck tick"
	gettime(90)
	
	if(get(90) = 0) {
		print "Duck tick time"
		displayDateTime()
	}
}


func onAction(a, b) {
	clearMessageArea()
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

	draw(x / 2, 127 - 16, 20);
	draw(X / 2, 127 - 8, 21);
}


func appletInit() {
	fg(fgColor)
	bg(bgColor)
	cls(bgColor)

	########
	# Clock Point List
	# Array generated using https://jsfiddle.net/jockm/6da3quv8/9/
	set(0, 0x32143200) #50,20 : 50,0
	set(1, 0x41183700) #65,24 : 55,0
	set(2, 0x4B233C01) #75,35 : 60,1
	set(3, 0x50324102) #80,50 : 65,2
	set(4, 0x4B414604) #75,65 : 70,4
	set(5, 0x414B4B06) #65,75 : 75,6
	set(6, 0x32504F09) #50,80 : 79,9
	set(7, 0x234B530C) #35,75 : 83,12
	set(8, 0x18415710) #24,65 : 87,16
	set(9, 0x14325A14) #20,50 : 90,20
	set(10, 0x18235D19) #24,35 : 93,25
	set(11, 0x22185F1D) #34,24 : 95,29
	set(12, 0x6122) #0,0 : 97,34
	set(13, 0x6227) #0,0 : 98,39
	set(14, 0x632C) #0,0 : 99,44
	set(15, 0x6432) #0,0 : 100,50
	set(16, 0x6337) #0,0 : 99,55
	set(17, 0x623C) #0,0 : 98,60
	set(18, 0x6141) #0,0 : 97,65
	set(19, 0x5F46) #0,0 : 95,70
	set(20, 0x5D4B) #0,0 : 93,75
	set(21, 0x5A4F) #0,0 : 90,79
	set(22, 0x5753) #0,0 : 87,83
	set(23, 0x5357) #0,0 : 83,87
	set(24, 0x4F5A) #0,0 : 79,90
	set(25, 0x4B5D) #0,0 : 75,93
	set(26, 0x465F) #0,0 : 70,95
	set(27, 0x4161) #0,0 : 65,97
	set(28, 0x3C62) #0,0 : 60,98
	set(29, 0x3763) #0,0 : 55,99
	set(30, 0x3264) #0,0 : 50,100
	set(31, 0x2C63) #0,0 : 44,99
	set(32, 0x2762) #0,0 : 39,98
	set(33, 0x2261) #0,0 : 34,97
	set(34, 0x1D5F) #0,0 : 29,95
	set(35, 0x195D) #0,0 : 25,93
	set(36, 0x145A) #0,0 : 20,90
	set(37, 0x1057) #0,0 : 16,87
	set(38, 0xC53) #0,0 : 12,83
	set(39, 0x94F) #0,0 : 9,79
	set(40, 0x64B) #0,0 : 6,75
	set(41, 0x446) #0,0 : 4,70
	set(42, 0x241) #0,0 : 2,65
	set(43, 0x13C) #0,0 : 1,60
	set(44, 0x37) #0,0 : 0,55
	set(45, 0x32) #0,0 : 0,50
	set(46, 0x2C) #0,0 : 0,44
	set(47, 0x127) #0,0 : 1,39
	set(48, 0x222) #0,0 : 2,34
	set(49, 0x41D) #0,0 : 4,29
	set(50, 0x619) #0,0 : 6,25
	set(51, 0x914) #0,0 : 9,20
	set(52, 0xC10) #0,0 : 12,16
	set(53, 0x100C) #0,0 : 16,12
	set(54, 0x1409) #0,0 : 20,9
	set(55, 0x1806) #0,0 : 24,6
	set(56, 0x1D04) #0,0 : 29,4
	set(57, 0x2202) #0,0 : 34,2
	set(58, 0x2701) #0,0 : 39,1
	set(59, 0x2C00) #0,0 : 44,0

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

	circle(50 + marginX, 50 + marginY, 51)

	gettime(90)
	displayDateTime()
}

#<ul>
#  <script>
#  	// Thanks to T.J. Crowder for his massive help with this
#		const centerX = 50;
#		const centerY = 50;
#   
#	  function xCoord(centerX, radius, angleInRadians) {
#	    	return centerX + radius * Math.cos(angleInRadians);
#	  }
#	  
#	  
#	  function yCoord(centerY, radius, angleInRadians) {
#	    	return centerY + radius * Math.sin(angleInRadians);
#	  }
#  
#	function plotCircle(places, diameter, arr) {
#		const radius = diameter / 2;
#		const spacing = (2 * Math.PI) / places;
#		
#  	const angleAdjust = places / 4
#
#		for (let n = 0; n < places; ++n) {
#			const angleInRadians = spacing * (n - angleAdjust);
#
#			const x = xCoord(centerX, radius, angleInRadians);
#			const y = yCoord(centerY, radius, angleInRadians);
#
#			let a = [Math.trunc(x), Math.trunc(y)]
#			arr.push(a)
#		}
#
#	}
#
#	let hour = []
#	let min = []
#	plotCircle(12, 60, hour);
#	plotCircle(60, 100, min);
#	
#	let compacted = []
#	for(let i = 0; i < min.length; ++i) {
#		let v = 0
#		let h = [0, 0]
#		let m = min[i]
#
#		if(i < hour.length) {
#		h = hour[i]
#		} 
#
#		v |= h[0] << 24
#		v |= h[1] << 16
#		v |= m[0] << 8
#		v |= m[1]
#		document.write("<br>set(" + i + ", 0x" + v.toString(16).toUpperCase() + ") #" +h[0] +"," + h[1] + " : " + m[0] +"," + m[1])
#	}
#  </script>
#</ul>
