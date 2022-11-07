#define CIMGUI_DEFINE_ENUMS_AND_STRUCTS


//TO_EDIT

//Uses cvAddText and makes a border in a stupid way.
void cvAddTextBorder(float x, float y, unsigned int color, const char* text)
{
    cvAddText(x-0.02,y, CV_COL32_BLACK, text);
    cvAddText(x,y-0.02, CV_COL32_BLACK, text);
    cvAddText(x-0.02,y-0.02, CV_COL32_BLACK, text);
    cvAddText(x,y+0.02, CV_COL32_BLACK, text);
    cvAddText(x+0.02,y, CV_COL32_BLACK, text);
    cvAddText(x+0.02,y+0.02, CV_COL32_BLACK, text);
    cvAddText(x,y, color, text);
}