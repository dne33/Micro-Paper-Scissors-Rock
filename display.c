void display_character (char character)
{
    char buffer[2];
    buffer[0] = character;
    buffer[1] = '\0';
    tinygl_text (buffer);
}


void display_msg(char* message) 
{
    bool displaying = true;
    
    tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);
    tinygl_text(message);
    while (displaying) {
        pacer_wait ();
        tinygl_update ();
        navswitch_update ();
        if (navswitch_push_event_p (NAVSWITCH_NORTH)) {
           displaying = false;
        }
    }
}

void win_counter(int win_count)
{
    tinygl_point_t point = {win_count,6};
    tinygl_pixel_set(point,1);
    tinygl_update();
}
