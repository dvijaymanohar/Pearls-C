unsigned int hysteresis(unsigned int input_percent) {
  struct hys_thres {
    unsigned int thres_low;
    unsigned int thres_high;
    unsigned int thres_level;
  };

  const unsigned int thres_levels = 4;

  const struct hys_thres hys_thress[4] = {
      {10, 15, 1},
      {35, 40, 2},
      {60, 65, 3},
      {85, 90, 4},
  };

  static unsigned int discrete_thres_level;
  static unsigned int old_input;
  int i = 0;

  /* if the old value and the new value are same, return the same threshold
   * level */
  if (old_input == input_percent)
    return discrete_thres_level;

  if (input_percent > old_input) {
    for (i = thres_levels - 1; i >= 0; i--) {
      if (input_percent >= hys_thress[i].thres_high) {
        discrete_thres_level = hys_thress[i].thres_level;
        break;
      }
    }
  } else if (input_percent < old_input) {
    for (i = 0; i < thres_levels; i++) {
      if (input_percent <= hys_thress[i].thres_low) {
        discrete_thres_level = hys_thress[i].thres_level - 1;
        break;
      }
    }
  }

  old_input = input_percent;

  return discrete_thres_level;
}
