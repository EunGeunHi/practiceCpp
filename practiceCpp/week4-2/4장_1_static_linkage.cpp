//4Àå_static_linkage.cpp
int g = 2017;//static duration, external linkage
static int s = 20;//static duration, internal linkage
const int c = 30;//const global º¯¼ö
void show();
int main() {
	show();
	show();
	return 0;
}
void show() {
	static int n = 0;//static duration, no linkage
	//...
	n++;
		return 0;
}