/*
	problematic - an error message generator
	Copyright (C) 2020 Grace Lovelace

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU Affero General Public License as published
	by the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU Affero General Public License for more details.

	You should have received a copy of the GNU Affero General Public License
	along with this program.  If not, see <https://www.gnu.org/licenses/>.

	For license inquiries, contact grace@hypnovir.us

	Source code and license available at https://github.com/Kansattica/problematic

	USAGE:

	compile like this:

		g++ -std=c++17 -O3 problematic.cpp -o problematic

	run like this:

		./problematic asdf | pv q -L 300

	problematic produces a lot of output as fast as it can, so something like pv or head will help a lot.

	Starting problematic with at least one command line argument will print colorful errors.
*/


#include <iostream>
#include <string_view>
#include <vector>
#include <random>
#include <array>
#include <string>

static std::minstd_rand randy{std::random_device{}()};

std::string& rainbowify(std::string& torainbow, std::size_t chunk)
{
	// reference for color codes is: https://stackoverflow.com/a/33206814/5587653
	static constexpr std::array<std::string_view, 14> colors =
			{
					"\033[38;5;196m",
					"\033[38;5;199m",
					"\033[38;5;205m",
					"\033[38;5;202m",
					"\033[38;5;208m",
					"\033[38;5;214m",
					"\033[38;5;112m",
					"\033[38;5;40m",
					"\033[38;5;45m",
					"\033[38;5;27m",
					"\033[38;5;129m",
					"\033[38;5;91m",
					"\033[38;5;162m",
					"\033[38;5;197m"
			};

	std::size_t color = 0;
	if (chunk == 0)
	{
		for (std::size_t idx = 0; idx != std::string::npos; idx = torainbow.find_first_of(" /.", idx + 1))
		{
			torainbow.insert(idx, colors[color]);
			idx += colors[color].size();
			color = (color + 1) % colors.size();
		}
	}
	else
	{
		for (std::size_t idx = 0; idx < torainbow.size(); idx += chunk)
		{
			torainbow.insert(idx, colors[color]);
			idx += colors[color].size();
			color = (color + 1) % colors.size();
		}
	}
	return torainbow;
}

template <typename T>
T take_sample(const std::vector<T>& tosample)
{
	std::uniform_int_distribution<int> dist(0, tosample.size()-1);
	return tosample[dist(randy)];
}

int number(int from, int to)
{
	std::uniform_int_distribution dist(from, to);
	return dist(randy);
}

char character()
{
	return '0' + number(0, 74);
}

static char to_return[30];
const char* randomstring(std::size_t length)
{
	for (std::size_t i = 0; i < length; i++)
		to_return[i] = character();
	to_return[length] = '\0';
	return to_return;
}

void print_credit(bool use_color)
{
	std::string credit = "problematic by Grace Danger Lovelace - 20XX - https://github.com/Kansattica/problematic - https://hypnovir.us\n";
	if (number(0, 2) == 0)
	{
		const std::vector<std::string_view> embellishment { "the lovely", "the perfect", "the delightful", "the one and only", "the villainous", "Vx.", "Princess", "the spellbinding", "the unmistakable", "the head-turning", "the unforgettable", "the villainous viral vixen", "the amazing", "the awe-inspiring", "the beloved" };
		credit.insert(14, 1, ' ');
		credit.insert(15, take_sample(embellishment));
	}
	if (use_color)
		std::cout << rainbowify(credit, number(0, 10));
	else
		std::cout << credit;
}

int main(int argc, char** argv)
{
	// unsync from C IO. Problematic doesn't need it.
	// problematic fills the buffer so fast, this is a significant perf boost
	// Especially since this flushes the buffer every newline if turned on.
	std::ios::sync_with_stdio(false);

	const bool use_color = argc > 1;
	const auto errlevels = !use_color ?
		std::vector<std::string_view>{ "INFO ", "WARN ", "ERROR", "AAAAH", "EMERG", "FATAL" } :
		std::vector<std::string_view>{ "\033[38;5;12mINFO ", "\033[38;5;11mWARN ", "\033[38;5;9mERROR", "\033[38;5;13mAAAAH", "\033[38;5;202mEMERG", "\033[38;5;207mFATAL" };
	const std::vector<std::string_view> sensor { "ARMNERV", "CPUCORE", "CIRCUIT", "GAYGAYGAY", "TEMP", "AUTOFIX", "PHYSBUF", "ADDER", "AIPROTO", "FAILSAFE", "!!!!", "/dev/tty", "/dev/null", "/dev/urandom", "RADIO", "RAD", "STABILITY", "MEMCHECK", "SERVO", "MOTOR", "???", "ENTROPY", "PASSWORD", "/etc/shadow", "HASH", "CONSISTENCY", "CHECKSUM", "ECHO", "PARITY", "CONCURRENCY", "THREAD", "lp", "OPERATION", "ATTEMPT", "PARTITION", "SEGMENTATION", "STACK", "HEAP", "BUFFER", "/var/spool", "KERNEL" };
	const std::vector<std::string_view> modifier { "", "", "", "", "", "", "", "", "", "", "", "", " POSSIBLY", " ILLEGAL", " ILLEGALLY", " EXTREMELY", " HAZARDOUSLY", " DANGEROUSLY", " VERY" };
	const std::vector<std::string_view> description { "CRITICAL", "OVERHEATING", "OVERLOADING", "OVERVOLT", "COOLANT", "CONSUMING", "CURIEPOINT", "LOST" , "PANIC", "DISRUPTION", "MELTING", "DISCONNECT", "EXHAUSTION", "RESERVE", "RETRY", "E-STOP", "OVERCHARGE", "UNDERCHARGE", "DEGRADATION", "OVERFLOW", "UNDERFLOW", "UNDERRUN" };
	const std::vector<std::string_view> problem { "LEAK", "SWELL", "INCALCULABLE", "NOT A TYPEWRITER", "ON FIRE", "GIRLS", "8==D", "SSSSSS", "COGNITOHAZARDOUS", "INFOHAZARD", "UNKNOWN", "IMPOSSIBLE", "INFINITE", "GRACEFUL", "UNRESPONSIVE", "UNRECOVERABLE", "HALT", "SHUTDOWN", "RESTART", "UNEXPECTED", "INCONCEIVABLE", "HAZARDOUS", "FAIL", "FAILURE", "PROBLEM", "ILLEGAL", "UNPARSEABLE", "VIRTUAL", "READONLY", "IRREVERSIBLE", "BURST", "LOAD LETTER", "FAULT", "GOOD", "BAD" };
	const std::vector<std::string_view> prefix { "", "", "/dev/", "/proc/", "/etc/", "/misc/", "/root/", "~/", "/bin/", "/boot/" };
	const std::vector<std::string_view> func { "void", "read", "write", "calibrate", "spunch", "wrangle", "mangle", "spangle", "decorate", "new", "alloc", "malloc", "twist", "spunch", "glunk", "bitblit", "fiasco", "main", "???", "!!!", "???????????", "unknown", "known", "connect", "put", "get", "swizzle", "assemble", "ruin", "futz", "dribble", "futz", "jig", "thunk", "thonk", "try", "catch", "finally", "final", "parse", "swap", "trade", "atomic", "float", "operator,", "operator<<", "flip", "popcnt", "handle", "compile", "fix", "crinkle", "bend", "fold", "spindle", "spool", "init", "exit", "crash", "enter", "left", "right", "up", "down", "curl", "wcsrtombs", "sort", "shuffle", "transmute", "fork", "spoon", "exec", "cpy", "mov", "zot", "atoi", "itoa", "time", "strtok", "strzok", "fmp" };
	const std::vector<std::string_view> prefunc { "", "", "de", "un", "re", "0x", "_", "__", "!", "$", "?", "~", "&", "::", "__builtin_", "__cxx_", "mem", "str", "mk", "gm" };
	const std::vector<std::string_view> infunc { "in", "on", "around", "because of", "due to", "error from", "responsible for", "???" };
	const std::vector<std::string_view> funcargs { "()", "()", "(int)", "(int, float)", "(string&)", "(void*)", "(void**)", "(std::mt19937&)", "(int argv, char** argc)", "(??""?)" };

	print_credit(use_color);

	while (true)
	{
		std::cout << take_sample(errlevels) << " | " << take_sample(prefix) << take_sample(sensor) << number(0,99) << ' ' << take_sample(description) << take_sample(modifier) << ' ' << take_sample(problem) << (number(0, 10) ? "" : randomstring(number(1, 20))) << ' ';

		 for (int i = 0; i < number(1, 5); i++)
		 {
			 std::cout << take_sample(infunc) << ": " << take_sample(prefunc) << take_sample(func) << take_sample(funcargs) << ':' << number(1, 9999) << ", ";
		 }

		 std::cout << '\n';
	}

}
