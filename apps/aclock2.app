var fgColor = 0xFFFF
var bgColor = 255

var hColor = 0xFFFF
var mColor = 0xFFFF

var minXA = 0
var minYA = 0
var minXB = 0
var minYB = 0
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
	line(minXA + marginX, minYA + marginY, minXB + marginX, minYB + marginY)
	line(49 + marginX, 49 + marginY, hourX + marginX, hourY + marginY)
	

	# Get AM/PM and adjust hours to 0-11 

	if(h >= 11) {
		am = 0
		h = h - 12
	}

	# Draw the minutes line
	v = get(m + 20)
	minYA = v & 0xFF
	minXA = v >> 8 & 0xFF
	minYB = v >> 16 & 0xFF
	minXB = v >> 24 & 0xFF

	fg(mColor)
	line(minXA + marginX, minYA + marginY, minXB + marginX, minYB + marginY)

	# Draw the hours line
	v = get(h)
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
	gettime(90)
	
	if(get(90) = 0) {
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
	# Array generated using https://jsfiddle.net/jockm/3qvjr02t/

	# Hours
	set(0, 0x320B) #50,11
	set(1, 0x4510) #69,16
	set(2, 0x531E) #83,30
	set(3, 0x5932) #89,50
	set(4, 0x5345) #83,69
	set(5, 0x4553) #69,83
	set(6, 0x3259) #50,89
	set(7, 0x1E53) #30,83
	set(8, 0x1045) #16,69
	set(9, 0xB32) #11,50
	set(10, 0x101E) #16,30
	set(11, 0x1E10) #30,16
	
	# Minutes
	set(20, 0x320A3200) #50,10 : 50,0
	set(21, 0x360A3700) #54,10 : 55,0
	set(22, 0x3A0A3C01) #58,10 : 60,1
	set(23, 0x3E0B4102) #62,11 : 65,2
	set(24, 0x420D4604) #66,13 : 70,4
	set(25, 0x460F4B06) #70,15 : 75,6
	set(26, 0x49114F09) #73,17 : 79,9
	set(27, 0x4C14530C) #76,20 : 83,12
	set(28, 0x4F175710) #79,23 : 87,16
	set(29, 0x521A5A14) #82,26 : 90,20
	set(30, 0x541E5D19) #84,30 : 93,25
	set(31, 0x56215F1D) #86,33 : 95,29
	set(32, 0x58256122) #88,37 : 97,34
	set(33, 0x59296227) #89,41 : 98,39
	set(34, 0x592D632C) #89,45 : 99,44
	set(35, 0x5A326432) #90,50 : 100,50
	set(36, 0x59366337) #89,54 : 99,55
	set(37, 0x593A623C) #89,58 : 98,60
	set(38, 0x583E6141) #88,62 : 97,65
	set(39, 0x56425F46) #86,66 : 95,70
	set(40, 0x54465D4B) #84,70 : 93,75
	set(41, 0x52495A4F) #82,73 : 90,79
	set(42, 0x4F4C5753) #79,76 : 87,83
	set(43, 0x4C4F5357) #76,79 : 83,87
	set(44, 0x49524F5A) #73,82 : 79,90
	set(45, 0x46544B5D) #70,84 : 75,93
	set(46, 0x4256465F) #66,86 : 70,95
	set(47, 0x3E584161) #62,88 : 65,97
	set(48, 0x3A593C62) #58,89 : 60,98
	set(49, 0x36593763) #54,89 : 55,99
	set(50, 0x325A3264) #50,90 : 50,100
	set(51, 0x2D592C63) #45,89 : 44,99
	set(52, 0x29592762) #41,89 : 39,98
	set(53, 0x25582261) #37,88 : 34,97
	set(54, 0x21561D5F) #33,86 : 29,95
	set(55, 0x1E54195D) #30,84 : 25,93
	set(56, 0x1A52145A) #26,82 : 20,90
	set(57, 0x174F1057) #23,79 : 16,87
	set(58, 0x144C0C53) #20,76 : 12,83
	set(59, 0x1149094F) #17,73 : 9,79
	set(60, 0xF46064B) #15,70 : 6,75
	set(61, 0xD420446) #13,66 : 4,70
	set(62, 0xB3E0241) #11,62 : 2,65
	set(63, 0xA3A013C) #10,58 : 1,60
	set(64, 0xA360037) #10,54 : 0,55
	set(65, 0xA320032) #10,50 : 0,50
	set(66, 0xA2D002C) #10,45 : 0,44
	set(67, 0xA290127) #10,41 : 1,39
	set(68, 0xB250222) #11,37 : 2,34
	set(69, 0xD21041D) #13,33 : 4,29
	set(70, 0xF1E0619) #15,30 : 6,25
	set(71, 0x111A0914) #17,26 : 9,20
	set(72, 0x14170C10) #20,23 : 12,16
	set(73, 0x1714100C) #23,20 : 16,12
	set(74, 0x1A111409) #26,17 : 20,9
	set(75, 0x1D0F1806) #29,15 : 24,6
	set(76, 0x210D1D04) #33,13 : 29,4
	set(77, 0x250B2202) #37,11 : 34,2
	set(78, 0x290A2701) #41,10 : 39,1
	set(79, 0x2D0A2C00) #45,10 : 44,0
		
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
	circle(50 + marginX, 50 + marginY, 40)

	gettime(90)
	displayDateTime()
}