#ifndef COLORS_HPP
#define COLORS_HPP

#include <cairomm/context.h>

class Colors {
    public:
        static void set_color(const Cairo::RefPtr<Cairo::Context>& cr, int n) {
           switch(n % 83) {
               case 0:  cr->set_source_rgb(232.0/255.0, 94.0/255.0, 190.0/255.0); break;
               case 1:  cr->set_source_rgb(255.0/255.0,179.0/255.0,0.0); break;
               case 2:  cr->set_source_rgb(128.0/255.0, 62.0/255.0, 117.0/255.0); break;
               case 3:  cr->set_source_rgb(255.0/255.0, 104.0/255.0, 0.0/255.0); break;
               case 4:  cr->set_source_rgb(166.0/255.0, 189.0/255.0, 215.0/255.0); break;
               case 5:  cr->set_source_rgb(193.0/255.0, 0.0/255.0, 32.0/255.0); break;
               case 6:  cr->set_source_rgb(206.0/255.0, 162.0/255.0, 98.0/255.0); break;
               case 7:  cr->set_source_rgb(129.0/255.0, 112.0/255.0, 102.0/255.0); break;
               case 8:  cr->set_source_rgb(0.0/255.0, 125.0/255.0, 52.0/255.0); break;
               case 9:  cr->set_source_rgb(246.0/255.0, 118.0/255.0, 142.0/255.0); break;
               case 10: cr->set_source_rgb(0.0/255.0, 83.0/255.0, 138.0/255.0); break;
               case 11: cr->set_source_rgb(255.0/255.0, 122.0/255.0, 92.0/255.0); break;
               case 12: cr->set_source_rgb(83.0/255.0, 55.0/255.0, 122.0/255.0); break;
               case 13: cr->set_source_rgb(255.0/255.0, 142.0/255.0, 0.0/255.0); break;
               case 14: cr->set_source_rgb(179.0/255.0, 40.0/255.0, 81.0/255.0); break;
               case 15: cr->set_source_rgb(244.0/255.0, 200.0/255.0, 0.0/255.0); break;
               case 16: cr->set_source_rgb(127.0/255.0, 24.0/255.0, 13.0/255.0); break;
               case 17: cr->set_source_rgb(147.0/255.0, 170.0/255.0, 0.0/255.0); break;
               case 18: cr->set_source_rgb(89.0/255.0, 51.0/255.0, 21.0/255.0); break;
               case 19: cr->set_source_rgb(241.0/255.0, 58.0/255.0, 19.0/255.0); break;
               case 20: cr->set_source_rgb(35.0/255.0, 44.0/255.0, 22.0/255.0); break;
               case 21: cr->set_source_rgb(1.0/255.0, 0.0/255.0, 103.0/255.0); break;
               case 22: cr->set_source_rgb(213.0/255.0, 255.0/255.0, 0.0/255.0); break;
               case 23: cr->set_source_rgb(255.0/255.0, 0.0/255.0, 86.0/255.0); break;
               case 24: cr->set_source_rgb(158.0/255.0, 0.0/255.0, 142.0/255.0); break;
               case 25: cr->set_source_rgb(14.0/255.0, 76.0/255.0, 161.0/255.0); break;
               case 26: cr->set_source_rgb(255.0/255.0, 229.0/255.0, 2.0/255.0); break;
               case 27: cr->set_source_rgb(0.0/255.0, 95.0/255.0, 57.0/255.0); break;
               case 28: cr->set_source_rgb(0.0/255.0, 255.0/255.0, 0.0/255.0); break;
               case 29: cr->set_source_rgb(149.0/255.0, 0.0/255.0, 58.0/255.0); break;
               case 30: cr->set_source_rgb(255.0/255.0, 147.0/255.0, 126.0/255.0); break;
               case 31: cr->set_source_rgb(164.0/255.0, 36.0/255.0, 0.0/255.0); break;
               case 32: cr->set_source_rgb(0.0/255.0, 21.0/255.0, 68.0/255.0); break;
               case 33: cr->set_source_rgb(145.0/255.0, 208.0/255.0, 203.0/255.0); break;
               case 34: cr->set_source_rgb(98.0/255.0, 14.0/255.0, 0.0/255.0); break;
               case 35: cr->set_source_rgb(107.0/255.0, 104.0/255.0, 130.0/255.0); break;
               case 36: cr->set_source_rgb(0.0/255.0, 0.0/255.0, 255.0/255.0); break;
               case 37: cr->set_source_rgb(0.0/255.0, 125.0/255.0, 181.0/255.0); break;
               case 38: cr->set_source_rgb(106.0/255.0, 130.0/255.0, 108.0/255.0); break;
               case 39: cr->set_source_rgb(0.0/255.0, 174.0/255.0, 126.0/255.0); break;
               case 40: cr->set_source_rgb(194.0/255.0, 140.0/255.0, 159.0/255.0); break;
               case 41: cr->set_source_rgb(190.0/255.0, 153.0/255.0, 112.0/255.0); break;
               case 42: cr->set_source_rgb(0.0/255.0, 143.0/255.0, 156.0/255.0); break;
               case 43: cr->set_source_rgb(95.0/255.0, 173.0/255.0, 78.0/255.0); break;
               case 44: cr->set_source_rgb(255.0/255.0, 0.0/255.0, 0.0/255.0); break;
               case 45: cr->set_source_rgb(255.0/255.0, 0.0/255.0, 246.0/255.0); break;
               case 46: cr->set_source_rgb(255.0/255.0, 2.0/255.0, 157.0/255.0); break;
               case 47: cr->set_source_rgb(104.0/255.0, 61.0/255.0, 59.0/255.0); break;
               case 48: cr->set_source_rgb(255.0/255.0, 116.0/255.0, 163.0/255.0); break;
               case 49: cr->set_source_rgb(150.0/255.0, 138.0/255.0, 232.0/255.0); break;
               case 50: cr->set_source_rgb(152.0/255.0, 255.0/255.0, 82.0/255.0); break;
               case 51: cr->set_source_rgb(167.0/255.0, 87.0/255.0, 64.0/255.0); break;
               case 52: cr->set_source_rgb(1.0/255.0, 255.0/255.0, 254.0/255.0); break;
               case 53: cr->set_source_rgb(255.0/255.0, 238.0/255.0, 232.0/255.0); break;
               case 54: cr->set_source_rgb(254.0/255.0, 137.0/255.0, 0.0/255.0); break;
               case 55: cr->set_source_rgb(189.0/255.0, 198.0/255.0, 255.0/255.0); break;
               case 56: cr->set_source_rgb(1.0/255.0, 208.0/255.0, 255.0/255.0); break;
               case 57: cr->set_source_rgb(187.0/255.0, 136.0/255.0, 0.0/255.0); break;
               case 58: cr->set_source_rgb(117.0/255.0, 68.0/255.0, 177.0/255.0); break;
               case 59: cr->set_source_rgb(165.0/255.0, 255.0/255.0, 210.0/255.0); break;
               case 60: cr->set_source_rgb(255.0/255.0, 166.0/255.0, 254.0/255.0); break;
               case 61: cr->set_source_rgb(119.0/255.0, 77.0/255.0, 0.0/255.0); break;
               case 62: cr->set_source_rgb(122.0/255.0, 71.0/255.0, 130.0/255.0); break;
               case 63: cr->set_source_rgb(38.0/255.0, 52.0/255.0, 0.0/255.0); break;
               case 64: cr->set_source_rgb(0.0/255.0, 71.0/255.0, 84.0/255.0); break;
               case 65: cr->set_source_rgb(67.0/255.0, 0.0/255.0, 44.0/255.0); break;
               case 66: cr->set_source_rgb(181.0/255.0, 0.0/255.0, 255.0/255.0); break;
               case 67: cr->set_source_rgb(255.0/255.0, 177.0/255.0, 103.0/255.0); break;
               case 68: cr->set_source_rgb(255.0/255.0, 219.0/255.0, 102.0/255.0); break;
               case 69: cr->set_source_rgb(144.0/255.0, 251.0/255.0, 146.0/255.0); break;
               case 70: cr->set_source_rgb(126.0/255.0, 45.0/255.0, 210.0/255.0); break;
               case 71: cr->set_source_rgb(189.0/255.0, 211.0/255.0, 147.0/255.0); break;
               case 72: cr->set_source_rgb(229.0/255.0, 111.0/255.0, 254.0/255.0); break;
               case 73: cr->set_source_rgb(222.0/255.0, 255.0/255.0, 116.0/255.0); break;
               case 74: cr->set_source_rgb(0.0/255.0, 255.0/255.0, 120.0/255.0); break;
               case 75: cr->set_source_rgb(0.0/255.0, 155.0/255.0, 255.0/255.0); break;
               case 76: cr->set_source_rgb(0.0/255.0, 100.0/255.0, 1.0/255.0); break;
               case 77: cr->set_source_rgb(0.0/255.0, 118.0/255.0, 255.0/255.0); break;
               case 78: cr->set_source_rgb(133.0/255.0, 169.0/255.0, 0.0/255.0); break;
               case 79: cr->set_source_rgb(0.0/255.0, 185.0/255.0, 23.0/255.0); break;
               case 80: cr->set_source_rgb(120.0/255.0, 130.0/255.0, 49.0/255.0); break;
               case 81: cr->set_source_rgb(0.0/255.0, 255.0/255.0, 198.0/255.0); break;
               case 82: cr->set_source_rgb(255.0/255.0, 110.0/255.0, 65.0/255.0); break;
          }
        };
};

#endif // COLORS_HPP
