#ifndef SETTINGS_H
#define SETTINGS_H

typedef struct {
  bool use_american_date_format;
  bool vibe_on_hour;
  bool invert_colors;
  bool display_year;
} Settings;
extern Settings settings;

void init_settings();
void display_settings();
void deinit_settings();

#endif  // SETTINGS_H
