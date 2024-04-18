#ifdef __has_include
    #if __has_include("lvgl.h")
        #ifndef LV_LVGL_H_INCLUDE_SIMPLE
            #define LV_LVGL_H_INCLUDE_SIMPLE
        #endif
    #endif
#endif

#if defined(LV_LVGL_H_INCLUDE_SIMPLE)
    #include "lvgl.h"
#else
    #include "lvgl/lvgl.h"
#endif


#ifndef LV_ATTRIBUTE_MEM_ALIGN
#define LV_ATTRIBUTE_MEM_ALIGN
#endif

#ifndef LV_ATTRIBUTE_IMG_GEAR_3
#define LV_ATTRIBUTE_IMG_GEAR_3
#endif

const LV_ATTRIBUTE_MEM_ALIGN LV_ATTRIBUTE_LARGE_CONST LV_ATTRIBUTE_IMG_GEAR_3 uint8_t gear_3_map[] = {
  0x33, 0xcc, 0xff, 0xff, 0xff, 0xcc, 0x33, 
  0xcc, 0x33, 0x00, 0x00, 0x00, 0x33, 0xcc, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x33, 0xff, 
  0x00, 0x00, 0x00, 0x00, 0x33, 0xff, 0x33, 
  0x00, 0x00, 0x00, 0x33, 0xff, 0x33, 0x00, 
  0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 
  0xcc, 0x33, 0x00, 0x00, 0x00, 0x33, 0xcc, 
  0x33, 0xcc, 0xff, 0xff, 0xff, 0xcc, 0x29, 
};

const lv_img_dsc_t gear_3 = {
  .header.cf = LV_IMG_CF_ALPHA_8BIT,
  .header.always_zero = 0,
  .header.reserved = 0,
  .header.w = 7,
  .header.h = 11,
  .data_size = 77,
  .data = gear_3_map,
};
