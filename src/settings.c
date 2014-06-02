#include <pebble.h>

#include "settings.h"

Window* menu_window;
SimpleMenuLayer* menu_layer;
static SimpleMenuSection menu_sections[1];
static SimpleMenuItem menu_items[4];

Settings settings;

void settings_callback(int index, void* context) {
  switch (index) {
    case 0: {
      if (settings.use_american_date_format) {
        settings.use_american_date_format = false;
        menu_items[index].subtitle = "Yes";
      } else {
        settings.use_american_date_format = true;
        menu_items[index].subtitle = "No";
      }
      break;
    }
    case 1: {
      if (settings.vibe_on_hour) {
        settings.vibe_on_hour = false;
        menu_items[index].subtitle = "Yes";
      } else {
        settings.vibe_on_hour = true;
        menu_items[index].subtitle = "No";
      }
      break;
    }
    case 2: {
      if (settings.invert_colors) {
        settings.invert_colors = false;
        menu_items[index].subtitle = "Yes";
      } else {
        settings.invert_colors = true;
        menu_items[index].subtitle = "No";
      }
      break;
    }
    case 3: {
      if (settings.display_year) {
        settings.display_year = false;
        menu_items[index].subtitle = "Year";
      } else {
        settings.display_year = true;
        menu_items[index].subtitle = "Seconds";
      }
      break;
    }
  }
  menu_layer_reload_data((MenuLayer*)menu_layer);
}

void init_settings() {
  if (persist_read_data(0, &settings, sizeof(Settings)) == E_DOES_NOT_EXIST) {
    settings.use_american_date_format = false;
    settings.vibe_on_hour = false;
    settings.invert_colors = false;
    settings.display_year = false;
  }

  menu_window = window_create();
  menu_items[0] = (SimpleMenuItem) {
    .title = "Use American date format?",
    .callback = &settings_callback
  };
  menu_items[1] = (SimpleMenuItem) {
    .title = "Vibrate on the hour?",
    .callback = &settings_callback
  };
  menu_items[2] = (SimpleMenuItem) {
    .title = "Invert colors?",
    .callback = &settings_callback
  };
  menu_items[3] = (SimpleMenuItem) {
    .title = "Display year or seconds?",
    .callback = &settings_callback
  };
  menu_sections[0] = (SimpleMenuSection) {
    .title = NULL,
    .items = menu_items,
    .num_items = ARRAY_LENGTH(menu_items)
  };
  menu_layer = simple_menu_layer_create(
      layer_get_frame(window_get_root_layer(menu_window)), menu_window,
      menu_sections, ARRAY_LENGTH(menu_sections), NULL);
  layer_add_child(window_get_root_layer(menu_window),
                  simple_menu_layer_get_layer(menu_layer));
}

void display_settings() {
  menu_items[0].subtitle = (settings.use_american_date_format? "Yes": "No");
  menu_items[1].subtitle = (settings.vibe_on_hour? "Yes": "No");
  menu_items[2].subtitle = (settings.invert_colors? "Yes": "No");
  menu_items[3].subtitle = (settings.display_year? "Year": "Seconds");
  window_stack_push(menu_window, true);
}

void deinit_settings() {
  persist_write_data(0, &settings, sizeof(Settings));

  window_destroy(menu_window);
  simple_menu_layer_destroy(menu_layer);
}
