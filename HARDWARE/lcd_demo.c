#include "main.h"

 void obj_add_anim()
{
    lv_anim_t a;
    memset(&a, 0, sizeof(lv_anim_t));

    lv_anim_t b;
    memset(&b, 0, sizeof(lv_anim_t));

    lv_obj_t *screen = lv_scr_act();
    lv_obj_t *obj = lv_obj_create(screen);
    lv_obj_t *obj1 = lv_obj_create(screen);
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 50, 50);
    lv_obj_set_style_bg_color(obj, lv_palette_main(LV_PALETTE_BLUE), 0);

    lv_obj_set_pos(obj1, 170, 0);
    lv_obj_set_size(obj1, 50, 50);
    lv_obj_set_style_bg_color(obj1, lv_palette_main(LV_PALETTE_PINK), 0);

    a.var = obj; // ????????

    a.exec_cb = (lv_anim_exec_xcb_t)lv_obj_set_y; // y?????
    a.time = lv_anim_speed_to_time(50, 0, 120);   // 1s????????
    a.start_value = 0;                            // ???????
    a.end_value = 120;                            // ????????

    a.act_time = -500; // ?????????????????500ms

    a.path_cb = lv_anim_path_bounce; // ?????????????
                                     // a.ready_cb = ready_call_back;  // ??????????? ?????

    a.playback_time = 1;    // ?????????????
    a.playback_delay = 200; // ?????????

    a.repeat_cnt = 10000; // ???????????
    a.repeat_delay = 200; // ??????????????????
    lv_anim_start(&a);    // ???ú??????????

    b.var = obj1; // ????????

    b.exec_cb = (lv_anim_exec_xcb_t)lv_obj_set_y; // y?????
    b.time = lv_anim_speed_to_time(20, 0, 120);   // 1s????????
    b.start_value = 0;                            // ???????
    b.end_value = 120;                            // ????????

    b.act_time = -500; // ?????????????????500ms

    b.path_cb = lv_anim_path_bounce; // ?????????????
    // a.ready_cb = ready_call_back;  // ??????????? ?????

    b.playback_time = 1;    // ?????????????
    b.playback_delay = 200; // ?????????

    b.repeat_cnt = 10000;   // ???????????
    b.repeat_delay = 200; // ??????????????????
    lv_anim_start(&b);    // ???ú??????????
}

//************************************************************************************************
//example 3 示例3创建一个滑块并在标签上写入其值。

static lv_obj_t * label;

    static void slider_event_cb(lv_event_t * e)
    {
        lv_obj_t * slider = lv_event_get_target(e);

        /*Refresh the text*/
        lv_label_set_text_fmt(label, "%"LV_PRId32, lv_slider_get_value(slider));
        lv_obj_align_to(label, slider, LV_ALIGN_OUT_TOP_MID, 0, -15);    /*Align top of the slider*/
    }

    /**
     * Create a slider and write its value on a label.
     */
    void lv_example_get_started_3(void)
    {
        /*Create a slider in the center of the display*/
        lv_obj_t * slider = lv_slider_create(lv_scr_act());
        lv_obj_set_width(slider, 200);                          /*Set the width*/
        lv_obj_center(slider);                                  /*Align to the center of the parent (screen)*/
        lv_obj_add_event_cb(slider, slider_event_cb, LV_EVENT_VALUE_CHANGED, NULL);     /*Assign an event function*/

        /*Create a label above the slider*/
        label = lv_label_create(lv_scr_act());
        lv_label_set_text(label, "0");
        lv_obj_align_to(label, slider, LV_ALIGN_OUT_TOP_MID, 0, -15);    /*Align top of the slider*/
    }

//************************************************************************************************
//example 5 设置背景样式

    void lv_example_style_2(void)
    {
        static lv_style_t style;
        lv_style_init(&style);
        lv_style_set_radius(&style, 5);

        /*Make a gradient*/
        lv_style_set_bg_opa(&style, LV_OPA_COVER);
        static lv_grad_dsc_t grad;
        grad.dir = LV_GRAD_DIR_VER;
        grad.stops_count = 2;
        grad.stops[0].color = lv_palette_lighten(LV_PALETTE_GREY, 1);
        grad.stops[1].color = lv_palette_main(LV_PALETTE_BLUE);

        /*Shift the gradient to the bottom*/
        grad.stops[0].frac  = 128;
        grad.stops[1].frac  = 192;

        lv_style_set_bg_grad(&style, &grad);

        /*Create an object with the new style*/
        lv_obj_t * obj = lv_obj_create(lv_scr_act());
        lv_obj_add_style(obj, &style, 0);
        lv_obj_center(obj);
    }
//////////////////////////////////////////////////////////////////////////////////////////
//animation example
	
static void anim_x_cb(void * var, int32_t v)
{
    lv_obj_set_x(var, v);
}

static void anim_size_cb(void * var, int32_t v)
{
    lv_obj_set_size(var, v, v);
}

/**
 * Create a playback animation
 */
void lv_example_anim_2(void)
{

    lv_obj_t * obj = lv_obj_create(lv_scr_act());
    lv_obj_set_style_bg_color(obj, lv_palette_main(LV_PALETTE_RED), 0);
    lv_obj_set_style_radius(obj, LV_RADIUS_CIRCLE, 0);

    lv_obj_align(obj, LV_ALIGN_LEFT_MID, 10, 0);

    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_var(&a, obj);
    lv_anim_set_values(&a, 10, 50);
    lv_anim_set_time(&a, 1000);
    lv_anim_set_playback_delay(&a, 100);
    lv_anim_set_playback_time(&a, 300);
    lv_anim_set_repeat_delay(&a, 500);
    lv_anim_set_repeat_count(&a, LV_ANIM_REPEAT_INFINITE);
    lv_anim_set_path_cb(&a, lv_anim_path_ease_in_out);

    lv_anim_set_exec_cb(&a, anim_size_cb);
    lv_anim_start(&a);
    lv_anim_set_exec_cb(&a, anim_x_cb);
    lv_anim_set_values(&a, 10, 240);
    lv_anim_start(&a);
}

//////////////////////////////////////////////////////////////////////////
//lvglmenu样式
static lv_obj_t * list1;
static lv_obj_t * list2;

static lv_obj_t * currentButton = NULL;

static void event_handler(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_target(e);
    if(code == LV_EVENT_CLICKED) {
        LV_LOG_USER("Clicked: %s", lv_list_get_btn_text(list1, obj));

        if(currentButton == obj) {
            currentButton = NULL;
        }
        else {
            currentButton = obj;
        }
        lv_obj_t * parent = lv_obj_get_parent(obj);
        uint32_t i;
        for(i = 0; i < lv_obj_get_child_cnt(parent); i++) {
            lv_obj_t * child = lv_obj_get_child(parent, i);
            if(child == currentButton) {
                lv_obj_add_state(child, LV_STATE_CHECKED);
            }
            else {
                lv_obj_clear_state(child, LV_STATE_CHECKED);
            }
        }
    }
}

static void event_handler_top(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if(code == LV_EVENT_CLICKED) {
        if(currentButton == NULL) return;
        lv_obj_move_background(currentButton);
        lv_obj_scroll_to_view(currentButton, LV_ANIM_ON);
    }
}

static void event_handler_up(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if((code == LV_EVENT_CLICKED) || (code == LV_EVENT_LONG_PRESSED_REPEAT)) {
        if(currentButton == NULL) return;
        uint32_t index = lv_obj_get_index(currentButton);
        if(index <= 0) return;
        lv_obj_move_to_index(currentButton, index - 1);
        lv_obj_scroll_to_view(currentButton, LV_ANIM_ON);
    }
}

static void event_handler_center(lv_event_t * e)
{
    const lv_event_code_t code = lv_event_get_code(e);
    if((code == LV_EVENT_CLICKED) || (code == LV_EVENT_LONG_PRESSED_REPEAT)) {
        if(currentButton == NULL) return;

        lv_obj_t * parent = lv_obj_get_parent(currentButton);
        const uint32_t pos = lv_obj_get_child_cnt(parent) / 2;

        lv_obj_move_to_index(currentButton, pos);

        lv_obj_scroll_to_view(currentButton, LV_ANIM_ON);
    }
}

static void event_handler_dn(lv_event_t * e)
{
    const lv_event_code_t code = lv_event_get_code(e);
    if((code == LV_EVENT_CLICKED) || (code == LV_EVENT_LONG_PRESSED_REPEAT)) {
        if(currentButton == NULL) return;
        const uint32_t index = lv_obj_get_index(currentButton);

        lv_obj_move_to_index(currentButton, index + 1);
        lv_obj_scroll_to_view(currentButton, LV_ANIM_ON);
    }
}

static void event_handler_bottom(lv_event_t * e)
{
    const lv_event_code_t code = lv_event_get_code(e);
    if(code == LV_EVENT_CLICKED) {
        if(currentButton == NULL) return;
        lv_obj_move_foreground(currentButton);
        lv_obj_scroll_to_view(currentButton, LV_ANIM_ON);
    }
}

static void event_handler_swap(lv_event_t * e)
{
    const lv_event_code_t code = lv_event_get_code(e);
    // lv_obj_t* obj = lv_event_get_target(e);
    if((code == LV_EVENT_CLICKED) || (code == LV_EVENT_LONG_PRESSED_REPEAT)) {
        uint32_t cnt = lv_obj_get_child_cnt(list1);
        for(int i = 0; i < 100; i++)
            if(cnt > 1) {
                lv_obj_t * obj = lv_obj_get_child(list1, rand() % cnt);
                lv_obj_move_to_index(obj, rand() % cnt);
                if(currentButton != NULL) {
                    lv_obj_scroll_to_view(currentButton, LV_ANIM_ON);
                }
            }
    }
}

void lv_example_list_2(void)
{
    /*Create a list*/
    list1 = lv_list_create(lv_scr_act());
    lv_obj_set_size(list1, lv_pct(60), lv_pct(100));
    lv_obj_set_style_pad_row(list1, 5, 0);

    /*Add buttons to the list*/
    lv_obj_t * btn;
    int i;
    for(i = 0; i < 15; i++) {
        btn = lv_btn_create(list1);
        lv_obj_set_width(btn, lv_pct(50));
        lv_obj_add_event_cb(btn, event_handler, LV_EVENT_CLICKED, NULL);

        lv_obj_t * lab = lv_label_create(btn);
        lv_label_set_text_fmt(lab, "Item %d", i);
    }

    /*Select the first button by default*/
    currentButton = lv_obj_get_child(list1, 0);
    lv_obj_add_state(currentButton, LV_STATE_CHECKED);

    /*Create a second list with up and down buttons*/
    list2 = lv_list_create(lv_scr_act());
    lv_obj_set_size(list2, lv_pct(40), lv_pct(100));
    lv_obj_align(list2, LV_ALIGN_TOP_RIGHT, 0, 0);
    lv_obj_set_flex_flow(list2, LV_FLEX_FLOW_COLUMN);

    btn = lv_list_add_btn(list2, NULL, "Top");
    lv_obj_add_event_cb(btn, event_handler_top, LV_EVENT_ALL, NULL);
    lv_group_remove_obj(btn);

    btn = lv_list_add_btn(list2, LV_SYMBOL_UP, "Up");
    lv_obj_add_event_cb(btn, event_handler_up, LV_EVENT_ALL, NULL);
    lv_group_remove_obj(btn);

    btn = lv_list_add_btn(list2, LV_SYMBOL_LEFT, "Center");
    lv_obj_add_event_cb(btn, event_handler_center, LV_EVENT_ALL, NULL);
    lv_group_remove_obj(btn);

    btn = lv_list_add_btn(list2, LV_SYMBOL_DOWN, "Down");
    lv_obj_add_event_cb(btn, event_handler_dn, LV_EVENT_ALL, NULL);
    lv_group_remove_obj(btn);

    btn = lv_list_add_btn(list2, NULL, "Bottom");
    lv_obj_add_event_cb(btn, event_handler_bottom, LV_EVENT_ALL, NULL);
    lv_group_remove_obj(btn);

    btn = lv_list_add_btn(list2, LV_SYMBOL_SHUFFLE, "Shuffle");
    lv_obj_add_event_cb(btn, event_handler_swap, LV_EVENT_ALL, NULL);
    lv_group_remove_obj(btn);
}


/////////////////////////////////////////////////////////////////////////////////////
//lvgl 圆弧列表示例

/**
 * @brief 滚动结束后的事件
 * @param event 
*/
static void scroll_end_event(lv_event_t * e)
{
    lv_obj_t * cont = lv_event_get_target(e);                                               // 获取事件的初始对象
 
    /* 获取事件的事件代码 */
    if(lv_event_get_code(e) == LV_EVENT_SCROLL_END) 
    {  
        /* 判断是否在滚动中 */
        if (lv_obj_is_scrolling(cont))
        {
            return;
        }
 
        lv_coord_t child_cnt = lv_obj_get_child_cnt(cont);                                  // 获取子界面的数量
        lv_coord_t mid_btn_index = (child_cnt - 1) / 2;                                     // 中间界面的位置
 
        /* 获取父对象y轴的中心坐标值 */
        lv_area_t cont_a;
        lv_obj_get_coords(cont, &cont_a);                                                   // 将cont对象的坐标复制到cont_a
        lv_coord_t cont_y_center = cont_a.y1 + lv_area_get_width(&cont_a) / 2;              // 获取界面的宽像素大小/2 
 
        /* 注意，这里的中心显示界面的坐标不在正中心，所以这里加上了差值 */
        cont_y_center += 69;
 
        /* 遍历子界面 */
        for (lv_coord_t i = 0; i < child_cnt; i++) {
            lv_obj_t* child = lv_obj_get_child(cont, i);                                    // 通过索引获取子对象
 
            /* 获取子对象y轴的中心坐标值 */
            lv_area_t child_a;
            lv_obj_get_coords(child, &child_a);
            lv_coord_t child_y_center = child_a.y1 + lv_area_get_width(&child_a) / 2;       // 获取界面中按钮宽像素值的大小/2
            /* 子界面的坐标与父界面的坐标相等时，说明当前界面在父界面中显示 */
            if (child_y_center == cont_y_center)
            {
                /* 当前显示界面的索引 */
                lv_coord_t current_btn_index = lv_obj_get_index(child);
 
                /* 判断界面移动的数数据，并将当前界面的索引改为中间位置 */
                /* 因为是在滑动结束后实现的，建议界面较多的情况下使用此方式，当界面较少，一次滑动太多界面时，容易滑倒边界出现卡顿现象 */
                lv_coord_t move_btn_quantity = LV_ABS(current_btn_index - mid_btn_index);
                for (lv_coord_t j = 0; j < move_btn_quantity; j++)
                {
                    /* 向右滑动 */
                    if (current_btn_index < mid_btn_index)
                    {
                        lv_obj_move_to_index(lv_obj_get_child(cont, child_cnt - 1), 0);                     // 将最后一个界面索引改为第一个界面
                        lv_obj_scroll_to_view(lv_obj_get_child(cont, mid_btn_index), LV_ANIM_OFF);          // lv_obj_get_child 通过子索引获取对象的子对象
                    }
                    /* 向左滑动 */
                    if (current_btn_index > mid_btn_index)
                    {
                        lv_obj_move_to_index(lv_obj_get_child(cont, 0), child_cnt - 1);                     // 将第一个界面的索引值改为最后一个界面
                        lv_obj_scroll_to_view(lv_obj_get_child(cont, mid_btn_index), LV_ANIM_OFF);          // lv_obj_get_child 通过子索引获取对象的子对象
                    }
                }
                /* 保证界面居中显示 */
                lv_obj_set_style_translate_y(lv_obj_get_child(cont, mid_btn_index), 0, 0);
                break;
            }
        }            
    }
}
 
static void scroll_event_cb(lv_event_t * e)
{
    lv_obj_t * cont = lv_event_get_target(e);
 
    lv_area_t cont_a;
    lv_obj_get_coords(cont, &cont_a);
    lv_coord_t cont_y_center = cont_a.y1 + lv_area_get_height(&cont_a) / 2;
 
    lv_coord_t r = lv_obj_get_height(cont) * 7 / 10;
    uint32_t i;
    uint32_t child_cnt = lv_obj_get_child_cnt(cont);
    for(i = 0; i < child_cnt; i++) {
        lv_obj_t * child = lv_obj_get_child(cont, i);
        lv_area_t child_a;
        lv_obj_get_coords(child, &child_a);
 
        lv_coord_t child_y_center = child_a.y1 + lv_area_get_height(&child_a) / 2;
 
        lv_coord_t diff_y = child_y_center - cont_y_center;
        diff_y = LV_ABS(diff_y);
 
        /*Get the x of diff_y on a circle.*/
        lv_coord_t x;
        /*If diff_y is out of the circle use the last point of the circle (the radius)*/
        if(diff_y >= r) {
            x = r;
        }
        else {
            /*Use Pythagoras theorem to get x from radius and y*/
            uint32_t x_sqr = r * r - diff_y * diff_y;
            lv_sqrt_res_t res;
            lv_sqrt(x_sqr, &res, 0x8000);   /*Use lvgl's built in sqrt root function*/
            x = r - res.i;
        }
 
        /*Translate the item by the calculated X coordinate*/
        lv_obj_set_style_translate_x(child, x, 0);
 
        /*Use some opacity with larger translations*/
        lv_opa_t opa = lv_map(x, 0, r, LV_OPA_TRANSP, LV_OPA_COVER);
        lv_obj_set_style_opa(child, LV_OPA_COVER - opa, 0);
    }
}
 
/**
 * Translate the object as they scroll
 */
void lvgl_scroll_test(void)
{
    lv_obj_t * cont = lv_obj_create(lv_scr_act());
    lv_obj_set_size(cont, 360, 360);
    lv_obj_center(cont);
    lv_obj_set_flex_flow(cont, LV_FLEX_FLOW_COLUMN);
 
    lv_obj_add_event_cb(cont, scroll_event_cb, LV_EVENT_SCROLL, NULL);       // 为了方便实现，先把滚动的动画屏蔽
    //lv_obj_add_event_cb(cont, scroll_end_event, LV_EVENT_SCROLL_END, NULL);
 
    lv_obj_set_style_radius(cont, LV_RADIUS_CIRCLE, 0);
    lv_obj_set_style_clip_corner(cont, true, 0);
    lv_obj_set_scroll_dir(cont, LV_DIR_VER);
    lv_obj_set_scroll_snap_y(cont, LV_SCROLL_SNAP_CENTER);
    lv_obj_set_scrollbar_mode(cont, LV_SCROLLBAR_MODE_OFF);
 
    uint32_t i;
    for(i = 0; i < 20; i++) {
        lv_obj_t * btn = lv_btn_create(cont);
        lv_obj_set_width(btn, lv_pct(80));
		lv_obj_set_height(btn,lv_pct(40));
		lv_obj_set_style_radius(btn,80,0);
		
        lv_obj_t * label = lv_label_create(btn);
        lv_label_set_text_fmt(label, "Button %"LV_PRIu32, i);
    }
 
    /*---------------------------------------- 指定中心显示界面 ----------------------------------------*/
    lv_coord_t mid_btn_index = (lv_obj_get_child_cnt(cont) - 1) / 2;                   // 如果界面为偶数，将中间数向下取整的界面设置为中间界面
    lv_coord_t child_cnt = lv_obj_get_child_cnt(cont);                                 // 获取子界面的数量
 
    int roll_direction = mid_btn_index - mid_btn_index;                                      // 确定滚动方向
 
    /* 通过循环将指定界面移到中心位置 */
    for (lv_coord_t i = 0; i < LV_ABS(roll_direction); i++)
    {
        if (roll_direction > 0)
        {
            lv_obj_move_to_index(lv_obj_get_child(cont, child_cnt - 1), 0);            // 将最后一个界面的索引更改为 0 （移至第一个界面）
        }
        else
        {
            lv_obj_move_to_index(lv_obj_get_child(cont, 0), child_cnt - 1);            // 将第一个界面的索引值改为最大值（移至最后一个界面）
        }    
    }
 
    /*当按钮数为偶数时，确保按钮居中*/
    lv_obj_scroll_to_view(lv_obj_get_child(cont, mid_btn_index), LV_ANIM_OFF);         // 滚动到一个对象，直到它在其父对象上可见
}
