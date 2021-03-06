#include "emu.h"

void emu_step(struct emuctx *ctx)
{
    byte opcode = read_byte(ctx) ;
    next_ip(ctx) ;
    switch (opcode)
    {
        case 0x00:
        { // add reg8/mem8, reg8
            int addr = decodeEA(ctx) ;
            if (is_reg(ctx))
            {
                byte left_reg = get_reg8(ctx, addr) ;
                byte right_reg = get_reg8(ctx, get_regRM(ctx)) ;
                byte result = left_reg + right_reg ;
                set_reg8(ctx, addr, result) ;
                set_cf_byte(ctx, left_reg+right_reg) ;
                set_of_byte(ctx, left_reg, right_reg, result)  ;
                if (((left_reg & 0x0F) + (right_reg & 0x0F)) & 0x10) set_af(ctx, YES) ;
                else set_af(ctx, NO) ;
                is_parity_byte(ctx, result) ;
                is_zero_byte(ctx, result) ;
                is_sign_byte(ctx, result) ; 
                set_cycles(ctx, 3) ;
            }
            else
            {
                byte left_reg = read_mem_byte(ctx, addr) ;
                byte right_reg = get_reg8(ctx, get_regRM(ctx)) ;
                byte result = left_reg + right_reg ;
                write_mem_byte(ctx, addr, result) ;
                set_cf_byte(ctx, left_reg+right_reg) ;
                set_of_byte(ctx, left_reg, right_reg, result)  ;
                if (((left_reg & 0x0F) + (right_reg & 0x0F)) & 0x10) set_af(ctx, YES) ;
                else set_af(ctx, NO) ;
                is_parity_byte(ctx, result) ;
                is_zero_byte(ctx, result) ;
                is_sign_byte(ctx, result) ; 
                set_cycles(ctx, 16) ;
            }
        } break ;
        case 0x01:
        { // add reg16/mem16, reg16
            int addr = decodeEA(ctx) ;
            if (is_reg(ctx))
            {
                word left_reg = get_reg16(ctx, addr) ;
                word right_reg = get_reg16(ctx, get_regRM(ctx)) ;
                word result ;
                result.w = left_reg.w + right_reg.w ;
                set_reg16(ctx, addr, result) ;
                set_cf_word(ctx, left_reg.w + right_reg.w) ;
                if (((left_reg.w & 0x0F) + (right_reg.w & 0x0F)) & 0x10) set_af(ctx, YES) ;
                else set_af(ctx, NO) ;
                set_of_word(ctx, right_reg, left_reg, result) ;
                is_parity_word(ctx, result) ;
                is_zero_word(ctx, result) ;
                is_sign_word(ctx, result) ; 
                set_cycles(ctx, 3) ;
            }
            else
            {
                word left_reg = read_mem_word(ctx, addr) ;
                word right_reg = get_reg16(ctx, get_regRM(ctx)) ;
                word result ;
                result.w = left_reg.w + right_reg.w ;
                write_mem_word(ctx, addr, result) ;
                set_cf_word(ctx, left_reg.w + right_reg.w) ;
                if (((left_reg.w & 0x0F) + (right_reg.w & 0x0F)) & 0x10) set_af(ctx, YES) ;
                else set_af(ctx, NO) ;
                set_of_word(ctx, right_reg, left_reg, result) ;
                is_parity_word(ctx, result) ;
                is_zero_word(ctx, result) ;
                is_sign_word(ctx, result) ;
                set_cycles(ctx, 16) ;
            }
        } break ;
        case 0x02:
        { // add reg8, reg8/mem8
            int addr = decodeEA(ctx) ;
            if (is_reg(ctx))
            {
                byte left_reg = get_reg8(ctx, get_regRM(ctx)) ;
                byte right_reg = get_reg8(ctx, addr) ;
                byte result = left_reg + right_reg ;
                set_reg8(ctx, addr, result) ;
                set_cf_byte(ctx, left_reg+right_reg) ;
                set_of_byte(ctx, left_reg, right_reg, result)  ;
                if (((left_reg & 0x0F) + (right_reg & 0x0F)) & 0x10) set_af(ctx, YES) ;
                else set_af(ctx, NO) ;
                is_parity_byte(ctx, result) ;
                is_zero_byte(ctx, result) ;
                is_sign_byte(ctx, result) ;
                set_cycles(ctx, 3) ;
            }
            else
            {
                byte left_reg = get_reg8(ctx, get_regRM(ctx)) ;
                byte right_reg = read_mem_byte(ctx, addr) ;
                byte result = left_reg + right_reg ;
                set_reg8(ctx, get_regRM(ctx), result) ; 
                set_cf_byte(ctx, left_reg+right_reg) ;
                set_of_byte(ctx, left_reg, right_reg, result)  ;
                if (((left_reg & 0x0F) + (right_reg & 0x0F)) & 0x10) set_af(ctx, YES) ;
                else set_af(ctx, NO) ;
                is_parity_byte(ctx, result) ;
                is_zero_byte(ctx, result) ;
                is_sign_byte(ctx, result) ; 
                set_cycles(ctx, 9) ;
            }
        } break ;
        case 0x03:
        { // add reg16, reg16/mem16
            int addr = decodeEA(ctx) ;
            if (is_reg(ctx))
            {
                word left_reg = get_reg16(ctx, addr) ;
                word right_reg = get_reg16(ctx, get_regRM(ctx)) ;
                word result ;
                result.w = left_reg.w + right_reg.w ;
                set_reg16(ctx, addr, result) ;
                set_cf_word(ctx, left_reg.w + right_reg.w) ;
                if (((left_reg.w & 0x0F) + (right_reg.w & 0x0F)) & 0x10) set_af(ctx, YES) ;
                else set_af(ctx, NO) ;
                set_of_word(ctx, right_reg, left_reg, result) ;
                is_parity_word(ctx, result) ;
                is_zero_word(ctx, result) ;
                is_sign_word(ctx, result) ; 
                set_cycles(ctx, 3) ;
            }
            else
            {
                word left_reg = get_reg16(ctx, get_regRM(ctx)) ; 
                word right_reg = read_mem_word(ctx, addr) ;
                word result ;
                result.w = left_reg.w + right_reg.w ;
                set_reg16(ctx, get_regRM(ctx), result) ;
                set_cf_word(ctx, left_reg.w + right_reg.w) ;
                if (((left_reg.w & 0x0F) + (right_reg.w & 0x0F)) & 0x10) set_af(ctx, YES) ;
                else set_af(ctx, NO) ;
                set_of_word(ctx, right_reg, left_reg, result) ;
                is_parity_word(ctx, result) ;
                is_zero_word(ctx, result) ;
                is_sign_word(ctx, result) ; 
                set_cycles(ctx, 9) ;
            }
        } break ;
        case 0x04:
        { // add al, immed8
            byte left_reg = get_reg8(ctx, AL) ;
            byte right_reg = next_byte(ctx) ;
            byte result = left_reg + right_reg ;
            set_reg8(ctx, AL, result) ;
            set_cf_byte(ctx, left_reg+right_reg) ;
            set_of_byte(ctx, left_reg, right_reg, result)  ;
            if (((left_reg & 0x0F) + (right_reg & 0x0F)) & 0x10) set_af(ctx, YES) ;
            else set_af(ctx, NO) ;
            is_parity_byte(ctx, result) ;
            is_zero_byte(ctx, result) ;
            is_sign_byte(ctx, result) ; 
            set_cycles(ctx, 4) ;
            
        } break ;
        case 0x05:
        { // add ax, immed16
            word left_reg = get_reg16(ctx, AX) ;
            word right_reg = next_word(ctx) ;
            word result ;
            result.w = left_reg.w + right_reg.w ;
            set_reg16(ctx, AX, result) ;
            set_cf_word(ctx, left_reg.w + right_reg.w) ;
            if (((left_reg.w & 0x0F) + (right_reg.w & 0x0F)) & 0x10) set_af(ctx, YES) ;
            else set_af(ctx, NO) ;
            set_of_word(ctx, right_reg, left_reg, result) ;
            is_parity_word(ctx, result) ;
            is_zero_word(ctx, result) ;
            is_sign_word(ctx, result) ;
            set_cycles(ctx, 4) ;
        } break ;
        case 0x06:
        { // push es
            
        } break ;
        case 0x07:
        { // pop es 
            
        } break ;
        case 0x08:
        { // or reg8/mem8, reg8
            int addr = decodeEA(ctx) ;
            if (is_reg(ctx))
            {
                byte left_reg = get_reg8(ctx, addr) ;
                byte right_reg = get_reg8(ctx, get_regRM(ctx)) ;
                byte result = left_reg | right_reg ;
                set_reg8(ctx, addr, result) ;
                set_cf(ctx, NO) ;
                set_of(ctx, NO) ;
                is_parity_byte(ctx, result) ;
                is_sign_byte(ctx, result) ;
                is_zero_byte(ctx, result) ;
                set_cycles(ctx, 3) ;
            }
            else
            {
                byte left_reg = read_mem_byte(ctx, addr) ;
                byte right_reg = get_reg8(ctx, get_regRM(ctx)) ;
                byte result = left_reg | right_reg ;
                write_mem_byte(ctx, addr, result) ;
                set_cf(ctx, NO) ;
                set_of(ctx, NO) ;
                is_parity_byte(ctx, result) ;
                is_sign_byte(ctx, result) ;
                is_zero_byte(ctx, result) ;
                set_cycles(ctx, 16) ;
            }
        } break ;
        case 0x09:
        { // or reg16/mem16, reg16
            int addr = decodeEA(ctx) ;
            if (is_reg(ctx))
            {
                word left_reg = get_reg16(ctx, addr) ;
                word right_reg = get_reg16(ctx, get_regRM(ctx)) ;
                word result ;
                result.w = left_reg.w | right_reg.w ;
                set_reg16(ctx, addr, result) ;
                set_cf(ctx, NO) ;
                set_of(ctx, NO) ;
                is_parity_word(ctx, result) ;
                is_sign_word(ctx, result) ;
                is_zero_word(ctx, result) ;
                set_cycles(ctx, 3) ;
            }
            else
            {
                word left_reg = read_mem_word(ctx, addr) ;
                word right_reg = get_reg16(ctx, get_regRM(ctx)) ;
                word result ;
                result.w = left_reg.w | right_reg.w ;
                write_mem_word(ctx, addr, result) ;
                set_cf(ctx, NO) ;
                set_of(ctx, NO) ;
                is_parity_word(ctx, result) ;
                is_sign_word(ctx, result) ;
                is_zero_word(ctx, result) ;
                set_cycles(ctx, 16) ;
            }
        } break ;
        case 0x0A:
        { // or reg8,reg8/mem8
            int addr = decodeEA(ctx) ;
            if (is_reg(ctx))
            {
                byte left_reg = get_reg8(ctx, get_regRM(ctx)) ;
                byte right_reg = get_reg8(ctx, addr) ;
                byte result = left_reg | right_reg ;
                set_reg8(ctx, addr, result) ;
                set_cf(ctx, NO) ;
                set_of(ctx, NO) ;
                is_parity_byte(ctx, result) ;
                is_sign_byte(ctx, result) ;
                is_zero_byte(ctx, result) ;
                set_cycles(ctx, 3) ;
            }
            else
            {
                byte left_reg = get_reg8(ctx, get_regRM(ctx)) ;
                byte right_reg = read_mem_byte(ctx, addr) ;
                byte result = left_reg | right_reg ;
                set_reg8(ctx, get_regRM(ctx), result) ; 
                set_cf(ctx, NO) ;
                set_of(ctx, NO) ;
                is_parity_byte(ctx, result) ;
                is_sign_byte(ctx, result) ;
                is_zero_byte(ctx, result) ;
                set_cycles(ctx, 9) ;
            }
        } break ;
        case 0x0B:
        { // or reg16, reg16/mem16
            int addr = decodeEA(ctx) ;
            if (is_reg(ctx))
            {
                word left_reg = get_reg16(ctx, addr) ;
                word right_reg = get_reg16(ctx, get_regRM(ctx)) ;
                word result ;
                result.w  = left_reg.w | right_reg.w ;
                set_reg16(ctx, addr, result) ;
                set_cf(ctx, NO) ;
                set_of(ctx, NO) ;
                is_parity_word(ctx, result) ;
                is_sign_word(ctx, result) ;
                is_zero_word(ctx, result) ;
                set_cycles(ctx, 3) ;
            }
            else
            {
                word left_reg = get_reg16(ctx, get_regRM(ctx)) ;
                word right_reg = read_mem_word(ctx, addr) ;
                word result ;
                result.w = left_reg.w | right_reg.w ;
                set_reg16(ctx, get_regRM(ctx), result) ; 
                set_cf(ctx, NO) ;
                set_of(ctx, NO) ;
                is_parity_word(ctx, result) ;
                is_sign_word(ctx, result) ;
                is_zero_word(ctx, result) ;
                set_cycles(ctx, 9) ;
            }
        } break ;
        case 0x0C:
        { // or al, immed8
            byte left_reg = get_reg8(ctx, AL) ;
            byte right_reg = next_byte(ctx) ;
            byte result = left_reg | right_reg ;
            set_reg8(ctx, AL, result) ;
            set_cf(ctx, NO) ;
            set_of(ctx, NO) ;
            is_parity_byte(ctx, result) ;
            is_sign_byte(ctx, result) ;
            is_zero_byte(ctx, result) ;
            set_cycles(ctx, 4) ;
            
        } break ;
        case 0x0D:
        { // or ax, immed16
            word left_reg = get_reg16(ctx, AX) ;
            word right_reg = next_word(ctx) ;
            word result ;
            result.w = left_reg.w | right_reg.w ;
            set_reg16(ctx, AX, result) ;
            set_cf(ctx, NO) ;
            set_of(ctx, NO) ;
            is_parity_word(ctx, result) ;
            is_sign_word(ctx, result) ;
            is_zero_word(ctx, result) ;
            set_cycles(ctx, 4) ;
        } break ;
        case 0x0E:
        { // push cs
            
        } break ;
        // 0x0f - not used
        case 0x10:
        { // adc reg8/mem8, reg8
            int addr = decodeEA(ctx) ;
            if (is_reg(ctx))
            {
                byte left_reg = get_reg8(ctx, addr) ;
                byte right_reg = get_reg8(ctx, get_regRM(ctx)) ;
                byte result = left_reg + right_reg + get_cf(ctx) ;
                set_reg8(ctx, addr, result) ;
                set_of_byte(ctx, left_reg, right_reg+get_cf(ctx), result)  ;
                if (((left_reg & 0x0F) + (right_reg & 0x0F) + get_cf(ctx)) & 0x10) set_af(ctx, YES) ;
                else set_af(ctx, NO) ;
                set_cf_byte(ctx, left_reg+right_reg+get_cf(ctx)) ;
                is_parity_byte(ctx, result) ;
                is_zero_byte(ctx, result) ;
                is_sign_byte(ctx, result) ;
                set_cycles(ctx, 3) ;
            }
            else
            {
                byte left_reg = read_mem_byte(ctx, addr) ;
                byte right_reg = get_reg8(ctx, get_regRM(ctx)) ;
                byte result = left_reg + right_reg + get_cf(ctx) ;
                write_mem_byte(ctx, addr, result) ;
                set_of_byte(ctx, left_reg, right_reg+get_cf(ctx), result)  ;
                if (((left_reg & 0x0F) + (right_reg & 0x0F) + get_cf(ctx)) & 0x10) set_af(ctx, YES) ;
                else set_af(ctx, NO) ;
                set_cf_byte(ctx, left_reg+right_reg+get_cf(ctx)) ;
                is_parity_byte(ctx, result) ;
                is_zero_byte(ctx, result) ;
                is_sign_byte(ctx, result) ;
                set_cycles(ctx, 16) ;
            }
        } break ;
        case 0x11:
        { // adc reg16/mem16, reg16
            int addr = decodeEA(ctx) ;
            if (is_reg(ctx))
            {
                word left_reg = get_reg16(ctx, addr) ;
                word right_reg = get_reg16(ctx, get_regRM(ctx)) ;
                word result ;
                result.w = left_reg.w + right_reg.w + get_cf(ctx) ;
                set_reg16(ctx, addr, result) ;
                word second_op ;
                second_op.w = right_reg.w + get_cf(ctx) ;
                set_of_word(ctx, left_reg, second_op, result) ;
                word_af_adc(ctx, left_reg, right_reg) ;
                set_cf_word(ctx, left_reg.w+right_reg.w+get_cf(ctx)) ;
                is_parity_word(ctx, result) ;
                is_zero_word(ctx, result) ;
                is_sign_word(ctx, result) ;
                set_cycles(ctx, 3) ;
            }
            else
            {
                word left_reg = read_mem_word(ctx, addr) ;
                word right_reg = get_reg16(ctx, get_regRM(ctx)) ;
                word result ;
                result.w = left_reg.w + right_reg.w + get_cf(ctx) ;
                write_mem_word(ctx, addr, result) ;
                word second_op ;
                second_op.w = right_reg.w + get_cf(ctx) ;
                set_of_word(ctx, left_reg, second_op, result) ;
                word_af_adc(ctx, left_reg, right_reg) ;
                set_cf_word(ctx, left_reg.w+right_reg.w+get_cf(ctx)) ;
                is_parity_word(ctx, result) ;
                is_zero_word(ctx, result) ;
                is_sign_word(ctx, result) ;
                set_cycles(ctx, 16) ;
            }
        } break ;
        case 0x12:
        { // adc reg8, reg8/mem8
            int addr = decodeEA(ctx) ;
            if (is_reg(ctx))
            {
                byte left_reg = get_reg8(ctx, get_regRM(ctx)) ;
                byte right_reg = get_reg8(ctx, addr) ;
                byte result = left_reg + right_reg + get_cf(ctx) ;
                set_reg8(ctx, addr, result) ;
                set_of_byte(ctx, left_reg, right_reg+get_cf(ctx), result)  ;
                if (((left_reg & 0x0F) + (right_reg & 0x0F) + get_cf(ctx)) & 0x10) set_af(ctx, YES) ;
                else set_af(ctx, NO) ;
                set_cf_byte(ctx, left_reg+right_reg+get_cf(ctx)) ;
                is_parity_byte(ctx, result) ;
                is_zero_byte(ctx, result) ;
                is_sign_byte(ctx, result) ;
                set_cycles(ctx, 3) ;
            }
            else
            {
                byte left_reg = get_reg8(ctx, get_regRM(ctx)) ;
                byte right_reg = read_mem_byte(ctx, addr) ;
                byte result = left_reg + right_reg + get_cf(ctx) ;
                set_reg8(ctx, get_regRM(ctx), result) ;
                set_of_byte(ctx, left_reg, right_reg+get_cf(ctx), result)  ;
                if (((left_reg & 0x0F) + (right_reg & 0x0F) + get_cf(ctx)) & 0x10) set_af(ctx, YES) ;
                else set_af(ctx, NO) ;
                set_cf_byte(ctx, left_reg+right_reg+get_cf(ctx)) ;
                is_parity_byte(ctx, result) ;
                is_zero_byte(ctx, result) ;
                is_sign_byte(ctx, result) ;
                set_cycles(ctx, 9) ;
            }
        } break ;
        case 0x13:
        { // adc reg16, reg16/mem16
            int addr = decodeEA(ctx) ;
            if (is_reg(ctx))
            {
                word left_reg = get_reg16(ctx, addr) ;
                word right_reg = get_reg16(ctx, get_regRM(ctx)) ;
                word result ;
                result.w = left_reg.w + right_reg.w + get_cf(ctx) ;
                set_reg16(ctx, addr, result) ;
                word second_op ;
                second_op.w = right_reg.w + get_cf(ctx) ;
                set_of_word(ctx, left_reg, second_op, result) ;
                word_af_adc(ctx, left_reg, right_reg) ;
                set_cf_word(ctx, left_reg.w+right_reg.w+get_cf(ctx)) ;
                is_parity_word(ctx, result) ;
                is_zero_word(ctx, result) ;
                is_sign_word(ctx, result) ;
                set_cycles(ctx, 3) ;
            }
            else
            {
                word left_reg = get_reg16(ctx, get_regRM(ctx)) ;
                word right_reg = read_mem_word(ctx, addr) ;
                word result ;
                result.w = left_reg.w + right_reg.w + get_cf(ctx) ;
                set_reg16(ctx, get_regRM(ctx), result) ;
                word second_op ;
                second_op.w = right_reg.w + get_cf(ctx) ;
                set_of_word(ctx, left_reg, second_op, result) ;
                word_af_adc(ctx, left_reg, right_reg) ;
                set_cf_word(ctx, left_reg.w+right_reg.w+get_cf(ctx)) ;
                is_parity_word(ctx, result) ;
                is_zero_word(ctx, result) ;
                is_sign_word(ctx, result) ;
                set_cycles(ctx, 9) ;
            }
        } break ;
        case 0x14:
        { // adc al, immed8
            byte left_reg = get_reg8(ctx, AL) ;
            byte right_reg = next_byte(ctx) ;
            byte result = left_reg + right_reg + get_cf(ctx) ;
            set_reg8(ctx, AL, result) ;
            set_of_byte(ctx, left_reg, right_reg+get_cf(ctx), result)  ;
            if (((left_reg & 0x0F) + (right_reg & 0x0F) + get_cf(ctx)) & 0x10) set_af(ctx, YES) ;
            else set_af(ctx, NO) ;
            set_cf_byte(ctx, left_reg+right_reg+get_cf(ctx)) ;
            is_parity_byte(ctx, result) ;
            is_zero_byte(ctx, result) ;
            is_sign_byte(ctx, result) ;
            set_cycles(ctx, 4) ;
        } break ;
        case 0x15:
        { // adc ax, immed16
            word left_reg = get_reg16(ctx, AX) ;
            word right_reg = next_word(ctx) ;
            word result ;
            result.w = left_reg.w + right_reg.w + get_cf(ctx) ;
            set_reg16(ctx, AX, result) ;
            word second_op ;
            second_op.w = right_reg.w + get_cf(ctx) ;
            set_of_word(ctx, left_reg, second_op, result) ;
            word_af_adc(ctx, left_reg, right_reg) ;
            set_cf_word(ctx, left_reg.w + (right_reg.w + get_cf(ctx))) ;
            is_parity_word(ctx, result) ;
            is_zero_word(ctx, result) ;
            is_sign_word(ctx, result) ;
            set_cycles(ctx, 4) ;
        } break ;
        case 0x16:
        { // push cs
            
        } break ;
        case 0x17:
        { // pop ss
            
        } break ;
        case 0x18:
        { // sbb reg8/mem8,reg8
            int addr = decodeEA(ctx) ;
            if (is_reg(ctx))
            {
                byte left_reg = get_reg8(ctx, addr) ;
                byte right_reg = get_reg8(ctx, get_regRM(ctx)) ;
                byte result = left_reg - (right_reg + get_cf(ctx)) ;
                set_reg8(ctx, addr, result) ;
                sbb_of_byte(ctx, left_reg, right_reg) ;
                sbb_cf_byte(ctx, left_reg, right_reg) ;
                sbb_af_byte(ctx, left_reg, right_reg) ; 
                is_parity_byte(ctx, result) ;
                is_zero_byte(ctx, result) ;
                is_sign_byte(ctx, result) ;
                set_cycles(ctx, 3) ;
            }
            else
            {
                byte left_reg = read_mem_byte(ctx, addr) ;
                byte right_reg = get_reg8(ctx, get_regRM(ctx)) ;
                byte result = left_reg - (right_reg + get_cf(ctx)) ;
                write_mem_byte(ctx, addr, result) ;
                sbb_of_byte(ctx, left_reg, right_reg) ;
                sbb_cf_byte(ctx, left_reg, right_reg) ;
                sbb_af_byte(ctx, left_reg, right_reg) ; 
                is_parity_byte(ctx, result) ;
                is_zero_byte(ctx, result) ;
                is_sign_byte(ctx, result) ;
                set_cycles(ctx, 16) ;
            }
        } break ;
        case 0x19:
        { // sbb reg16/mem16,reg16
            int addr = decodeEA(ctx) ;
            if (is_reg(ctx))
            {
                word left_reg = get_reg16(ctx, addr) ;
                word right_reg = get_reg16(ctx, get_regRM(ctx)) ;
                word result ;
                result.w = left_reg.w - (right_reg.w + get_cf(ctx)) ;
                set_reg16(ctx, addr, result) ;
                sbb_of_word(ctx, left_reg, right_reg) ;
                sbb_cf_word(ctx, left_reg, right_reg) ;
                sbb_af_word(ctx, left_reg, right_reg) ;
                is_parity_word(ctx, result) ;
                is_zero_word(ctx, result) ;
                is_sign_word(ctx, result) ;
                set_cycles(ctx, 3) ;
            }
            else
            {
                word left_reg = read_mem_word(ctx, addr) ;
                word right_reg = get_reg16(ctx, get_regRM(ctx)) ;
                word result ;
                result.w = left_reg.w - (right_reg.w + get_cf(ctx));
                write_mem_word(ctx, addr, result) ;
                sbb_of_word(ctx, left_reg, right_reg) ;
                sbb_cf_word(ctx, left_reg, right_reg) ;
                sbb_af_word(ctx, left_reg, right_reg) ;
                is_parity_word(ctx, result) ;
                is_zero_word(ctx, result) ;
                is_sign_word(ctx, result) ;
                set_cycles(ctx, 16) ;
            }
        } break ;
        case 0x1A:
        { // sbb reg8, reg8/mem8
            int addr = decodeEA(ctx) ;
            if (is_reg(ctx))
            {
                byte left_reg = get_reg8(ctx, get_regRM(ctx)) ;
                byte right_reg = get_reg8(ctx, addr) ;
                byte result = left_reg - (right_reg + get_cf(ctx));
                set_reg8(ctx, addr, result) ;
                sbb_of_byte(ctx, left_reg, right_reg) ;
                sbb_cf_byte(ctx, left_reg, right_reg) ;
                sbb_af_byte(ctx, left_reg, right_reg) ; 
                is_parity_byte(ctx, result) ;
                is_zero_byte(ctx, result) ;
                is_sign_byte(ctx, result) ;
                set_cycles(ctx, 3) ;
            }
            else
            {
                byte left_reg = get_reg8(ctx, get_regRM(ctx)) ;
                byte right_reg = read_mem_byte(ctx, addr) ;
                byte result = left_reg - (right_reg + get_cf(ctx));
                set_reg8(ctx, get_regRM(ctx), result) ;
                sbb_of_byte(ctx, left_reg, right_reg) ;
                sbb_cf_byte(ctx, left_reg, right_reg) ;
                sbb_af_byte(ctx, left_reg, right_reg) ; 
                is_parity_byte(ctx, result) ;
                is_zero_byte(ctx, result) ;
                is_sign_byte(ctx, result) ;
                set_cycles(ctx, 9) ;
            }
        } break ;
        case 0x1B:
        { // sbb reg16, reg16/mem16
            int addr = decodeEA(ctx) ;
            if (is_reg(ctx))
            {
                word left_reg = get_reg16(ctx, addr) ;
                word right_reg = get_reg16(ctx, get_regRM(ctx)) ;
                word result ;
                result.w = left_reg.w - (right_reg.w + get_cf(ctx)) ;
                set_reg16(ctx, addr, result) ;
                sbb_of_word(ctx, left_reg, right_reg) ;
                sbb_cf_word(ctx, left_reg, right_reg) ;
                sbb_af_word(ctx, left_reg, right_reg) ;
                is_parity_word(ctx, result) ;
                is_zero_word(ctx, result) ;
                is_sign_word(ctx, result) ;
                set_cycles(ctx, 3) ;
            }
            else
            {
                word left_reg = get_reg16(ctx, get_regRM(ctx)) ;
                word right_reg = read_mem_word(ctx, addr) ;
                word result ;
                result.w = left_reg.w - (right_reg.w + get_cf(ctx)) ;
                set_reg16(ctx, get_regRM(ctx), result) ;
                sbb_of_word(ctx, left_reg, right_reg) ;
                sbb_cf_word(ctx, left_reg, right_reg) ;
                sbb_af_word(ctx, left_reg, right_reg) ;
                is_parity_word(ctx, result) ;
                is_zero_word(ctx, result) ;
                is_sign_word(ctx, result) ;
                set_cycles(ctx, 9) ;
            }
        } break ;
        case 0x1C:
        { // sbb al, immed8
            byte left_reg = get_reg8(ctx, AL) ;
            byte right_reg = next_byte(ctx) ;
            byte result = left_reg - (right_reg + get_cf(ctx)) ;
            set_reg8(ctx, AL, result) ;
            sbb_of_byte(ctx, left_reg, right_reg) ;
            sbb_cf_byte(ctx, left_reg, right_reg) ;
            sbb_af_byte(ctx, left_reg, right_reg) ; 
            is_parity_byte(ctx, result) ;
            is_zero_byte(ctx, result) ;
            is_sign_byte(ctx, result) ;
            set_cycles(ctx, 4) ;
        } break ;
        case 0x1D:
        { // sbb ax, immed16
            word left_reg = get_reg16(ctx, AX) ;
            word right_reg = next_word(ctx) ;
            word result ;
            result.w = left_reg.w - (right_reg.w + get_cf(ctx)) ;
            set_reg16(ctx, AX, result) ;
            sbb_of_word(ctx, left_reg, right_reg) ;
            sbb_cf_word(ctx, left_reg, right_reg) ;
            sbb_af_word(ctx, left_reg, right_reg) ;
            is_parity_word(ctx, result) ;
            is_zero_word(ctx, result) ;
            is_sign_word(ctx, result) ;
            set_cycles(ctx, 4) ;
        } break ;
        case 0x1E:
        { // push ds
            
        } break ;
        case 0x1F:
        { // pop ds
            
        } break ;
        case 0x20:
        { // and reg8/mem8,reg8
            int addr = decodeEA(ctx) ;
            if (is_reg(ctx))
            {
                byte left_reg = get_reg8(ctx, addr) ;
                byte right_reg = get_reg8(ctx, get_regRM(ctx)) ;
                byte result = left_reg & right_reg ;
                set_reg8(ctx, addr, result) ;
                set_cf(ctx, NO) ;
                set_of(ctx, NO) ;
                set_cycles(ctx, 3) ;
            }
            else
            {
                byte left_reg = read_mem_byte(ctx, addr) ;
                byte right_reg = get_reg8(ctx, get_regRM(ctx)) ;
                byte result = left_reg & right_reg ;
                write_mem_byte(ctx, addr, result) ;
                set_cf(ctx, NO) ;
                set_of(ctx, NO) ;
                set_cycles(ctx, 16) ;
            }
        } break ;
        case 0x21:
        { // and reg16/mem16, reg16
            int addr = decodeEA(ctx) ;
            if (is_reg(ctx))
            {
                word left_reg = get_reg16(ctx, addr) ;
                word right_reg = get_reg16(ctx, get_regRM(ctx)) ;
                word result ;
                result.w = left_reg.w & right_reg.w ;
                set_reg16(ctx, addr, result) ;
                set_cf(ctx, NO) ;
                set_of(ctx, NO) ;
                set_cycles(ctx, 3) ;
            }
            else
            {
                word left_reg = read_mem_word(ctx, addr) ;
                word right_reg = get_reg16(ctx, get_regRM(ctx)) ;
                word result ;
                result.w = left_reg.w & right_reg.w ;
                write_mem_word(ctx, addr, result) ;
                set_cf(ctx, NO) ;
                set_of(ctx, NO) ;
                set_cycles(ctx, 16) ;
            }
        } break ;
        case 0x22:
        { // and reg8,reg8/mem8
            int addr = decodeEA(ctx) ;
            if (is_reg(ctx))
            {
                byte left_reg = get_reg8(ctx, get_regRM(ctx)) ;
                byte right_reg = get_reg8(ctx, addr) ;
                byte result = left_reg & right_reg ;
                set_reg8(ctx, addr, result) ;
                set_cf(ctx, NO) ;
                set_of(ctx, NO) ;
                set_cycles(ctx, 3) ;
            }
            else
            {
                byte left_reg = get_reg8(ctx, get_regRM(ctx)) ;
                byte right_reg = read_mem_byte(ctx, addr) ;
                byte result = left_reg & right_reg ;
                set_reg8(ctx, get_regRM(ctx), result) ;
                set_cf(ctx, NO) ;
                set_of(ctx, NO) ;
                set_cycles(ctx, 9) ;
            }
        } break ;
        case 0x23:
        { // and reg16,reg16/mem16
            int addr = decodeEA(ctx) ;
            if (is_reg(ctx))
            {
                word left_reg = get_reg16(ctx, addr) ;
                word right_reg = get_reg16(ctx, get_regRM(ctx)) ;
                word result ;
                result.w = left_reg.w & right_reg.w ;
                set_reg16(ctx, addr, result) ;
                set_cf(ctx, NO) ;
                set_of(ctx, NO) ;
                set_cycles(ctx, 3) ;
            }
            else
            {
                word left_reg = get_reg16(ctx, get_regRM(ctx)) ;
                word right_reg = read_mem_word(ctx, addr) ;
                word result ;
                result.w = left_reg.w & right_reg.w ;
                set_reg16(ctx, get_regRM(ctx), result) ;
                set_cf(ctx, NO) ;
                set_of(ctx, NO) ;
                set_cycles(ctx, 9) ;
            }
        } break ;
        case 0x24:
        { // and al,immed8
            byte left_reg = get_reg8(ctx, AL) ;
            byte right_reg = next_byte(ctx) ;
            byte result = left_reg & right_reg ;
            set_reg8(ctx, AL, result) ;
            set_cf(ctx, NO) ;
            set_of(ctx, NO) ;
            set_cycles(ctx, 4) ;
        } break ;
        case 0x25:
        { // and ax,immed16
            word left_reg = get_reg16(ctx, AX) ;
            word right_reg = next_word(ctx) ;
            word result ;
            result.w = left_reg.w & right_reg.w ;
            set_reg16(ctx, AX, result) ;
            set_cf(ctx, NO) ;
            set_of(ctx, NO) ;
            set_cycles(ctx, 4) ;
        } break ;
        case 0x26:
        { // es segment override
            
        } break ;
        case 0x27:
        { // daa
            if (((ctx->ax.b.l & 0x0F) > 9) || get_af(ctx) == YES)
            {
                ctx->ax.b.l = ctx->ax.b.l + 6 ;
                set_af(ctx, YES) ;
            }
            if ((ctx->ax.b.l > 0x9F) || get_cf(ctx) == YES)
            {
                ctx->ax.b.l = ctx->ax.b.l + 0x60 ;
                set_cf(ctx, YES) ;
            }
            is_sign_byte(ctx, ctx->ax.b.l) ;
            is_parity_byte(ctx, ctx->ax.b.l) ;
            is_zero_byte(ctx, ctx->ax.b.l) ;
            set_cycles(ctx, 4) ;
        } break ;
        case 0x28:
        { // sub reg8/mem8,reg8
            int addr = decodeEA(ctx) ;
            if (is_reg(ctx))
            {
                byte left_reg = get_reg8(ctx, addr) ;
                byte right_reg = get_reg8(ctx, get_regRM(ctx)) ;
                byte result = left_reg - right_reg ;
                set_reg8(ctx, addr, result) ;
                byte_cf_sub(ctx, left_reg, right_reg) ;
                byte_of_sub(ctx, left_reg, right_reg)  ;
                byte_af_sub(ctx, left_reg, right_reg) ;
                is_parity_byte(ctx, result) ;
                is_zero_byte(ctx, result) ;
                is_sign_byte(ctx, result) ;
                set_cycles(ctx, 3) ;
            }
            else
            {
                byte left_reg = read_mem_byte(ctx, addr) ;
                byte right_reg = get_reg8(ctx, get_regRM(ctx)) ;
                byte result = left_reg - right_reg ;
                write_mem_byte(ctx, addr, result) ;
                byte_cf_sub(ctx, left_reg, right_reg) ;
                byte_of_sub(ctx, left_reg, right_reg)  ;
                byte_af_sub(ctx, left_reg, right_reg) ;
                is_parity_byte(ctx, result) ;
                is_zero_byte(ctx, result) ;
                is_sign_byte(ctx, result) ;
                set_cycles(ctx, 16) ;
            }
        } break ;
        case 0x29:
        { // sub reg16/mem16,reg16
            int addr = decodeEA(ctx) ;
            if (is_reg(ctx))
            {
                word left_reg = get_reg16(ctx, addr) ;
                word right_reg = get_reg16(ctx, get_regRM(ctx)) ;
                word result ;
                result.w = left_reg.w - right_reg.w;
                set_reg16(ctx, addr, result) ;
                word_cf_sub(ctx, left_reg, right_reg) ;
                word_of_sub(ctx, left_reg, right_reg) ;
                word_af_sub(ctx, left_reg, right_reg) ;
                is_parity_word(ctx, result) ;
                is_zero_word(ctx, result) ;
                is_sign_word(ctx, result) ;
                set_cycles(ctx, 3) ;
            }
            else
            {
                word left_reg = read_mem_word(ctx, addr) ;
                word right_reg = get_reg16(ctx, get_regRM(ctx)) ;
                word result ;
                result.w = left_reg.w - right_reg.w;
                write_mem_word(ctx, addr, result) ;
                word_cf_sub(ctx, left_reg, right_reg) ;
                word_of_sub(ctx, left_reg, right_reg) ;
                word_af_sub(ctx, left_reg, right_reg) ;
                is_parity_word(ctx, result) ;
                is_zero_word(ctx, result) ;
                is_sign_word(ctx, result) ;
                set_cycles(ctx, 16) ;

            }
        } break ;
        case 0x2A:
        { // sub reg8,re8/mem8
            int addr = decodeEA(ctx) ;
            if (is_reg(ctx))
            {
                byte left_reg = get_reg8(ctx, get_regRM(ctx)) ;
                byte right_reg = get_reg8(ctx, addr) ;
                byte result = left_reg - right_reg;
                set_reg8(ctx, addr, result) ;
                byte_cf_sub(ctx, left_reg, right_reg) ;
                byte_of_sub(ctx, left_reg, right_reg) ;
                byte_af_sub(ctx, left_reg, right_reg) ;
                is_parity_byte(ctx, result) ;
                is_zero_byte(ctx, result) ;
                is_sign_byte(ctx, result) ;
                set_cycles(ctx, 3) ;
            }
            else
            {
                byte left_reg = get_reg8(ctx, get_regRM(ctx)) ;
                byte right_reg = read_mem_byte(ctx, addr) ;
                byte result = left_reg - right_reg;
                set_reg8(ctx, get_regRM(ctx), result) ;
                byte_cf_sub(ctx, left_reg, right_reg) ;
                byte_of_sub(ctx, left_reg, right_reg) ;
                byte_af_sub(ctx, left_reg, right_reg) ;
                is_parity_byte(ctx, result) ;
                is_zero_byte(ctx, result) ;
                is_sign_byte(ctx, result) ;
                set_cycles(ctx, 9) ;
            }
        } break ;
        case 0x2B:
        { // sub reg16,reg16/mem16
            int addr = decodeEA(ctx) ;
            if (is_reg(ctx))
            {
                word left_reg = get_reg16(ctx, addr) ;
                word right_reg = get_reg16(ctx, get_regRM(ctx)) ;
                word result ;
                result.w = left_reg.w - right_reg.w;
                set_reg16(ctx, addr, result) ;
                word_cf_sub(ctx, left_reg, right_reg) ;
                word_of_sub(ctx, left_reg, right_reg) ;
                word_af_sub(ctx, left_reg, right_reg) ;
                is_parity_word(ctx, result) ;
                is_zero_word(ctx, result) ;
                is_sign_word(ctx, result) ;
                set_cycles(ctx, 3) ;
            }
            else
            {
                word left_reg = get_reg16(ctx, get_regRM(ctx)) ;
                word right_reg = read_mem_word(ctx, addr) ;
                word result ;
                result.w = left_reg.w - right_reg.w;
                set_reg16(ctx, get_regRM(ctx), result) ;
                word_cf_sub(ctx, left_reg, right_reg) ;
                word_of_sub(ctx, left_reg, right_reg) ;
                word_af_sub(ctx, left_reg, right_reg) ;
                is_parity_word(ctx, result) ;
                is_zero_word(ctx, result) ;
                is_sign_word(ctx, result) ;
                set_cycles(ctx, 9) ;
            }
        } break ;
        case 0x2C:
        { // sub al,immed8
            byte left_reg = get_reg8(ctx, AL) ;
            byte right_reg = next_byte(ctx) ;
            byte result = left_reg - right_reg ;
            set_reg8(ctx, AL, result) ;
            byte_cf_sub(ctx, left_reg, right_reg) ;
            byte_af_sub(ctx, left_reg, right_reg) ;
            byte_of_sub(ctx, left_reg, right_reg) ;
            is_parity_byte(ctx, result) ;
            is_zero_byte(ctx, result) ;
            is_sign_byte(ctx, result) ;
            set_cycles(ctx, 4) ;
        } break ;
        case 0x2D:
        { // sub ax,immed16
            word left_reg = get_reg16(ctx, AX) ;
            word right_reg = next_word(ctx) ;
            word result ;
            result.w = left_reg.w - right_reg.w;
            set_reg16(ctx, AX, result) ;
            word_cf_sub(ctx, left_reg, right_reg) ;
            word_of_sub(ctx, left_reg, right_reg) ;
            word_af_sub(ctx, left_reg, right_reg) ;
            is_parity_word(ctx, result) ;
            is_zero_word(ctx, result) ;
            is_sign_word(ctx, result) ;
            set_cycles(ctx, 4) ;
        } break ;
        case 0x2E:
        { // cs - segment override
            
        } break ;
        case 0x2F:
        { // das
            if (((ctx->ax.b.l & 0x0F) > 9) || get_af(ctx) == YES)
            {
                ctx->ax.b.l = ctx->ax.b.l - 6 ;
                set_af(ctx, YES) ;
            }
            if ((ctx->ax.b.l > 0x9F) || get_cf(ctx) == YES)
            {
                ctx->ax.b.l = ctx->ax.b.l - 0x60 ;
                set_cf(ctx, YES) ;
            }
            is_sign_byte(ctx, ctx->ax.b.l) ;
            is_zero_byte(ctx, ctx->ax.b.l) ;
            is_parity_byte(ctx, ctx->ax.b.l) ;
        } break ;
        case 0x30:
        { // xor reg8/mem8,reg8
            int addr = decodeEA(ctx) ;
            if (is_reg(ctx))
            {
                byte left_reg = get_reg8(ctx, addr) ;
                byte right_reg = get_reg8(ctx, get_regRM(ctx)) ;
                byte result = left_reg ^ right_reg ;
                set_reg8(ctx, addr, result) ;
                set_cf(ctx, NO) ;
                set_of(ctx, NO) ;
                is_parity_byte(ctx, result) ;
                is_sign_byte(ctx, result) ;
                is_zero_byte(ctx, result) ;
                set_cycles(ctx, 3) ;
            }
            else
            {
                byte left_reg = read_mem_byte(ctx, addr) ;
                byte right_reg = get_reg8(ctx, get_regRM(ctx)) ;
                byte result = left_reg ^ right_reg ;
                write_mem_byte(ctx, addr, result) ;
                set_cf(ctx, NO) ;
                set_of(ctx, NO) ;
                is_parity_byte(ctx, result) ;
                is_sign_byte(ctx, result) ;
                is_zero_byte(ctx, result) ;
                set_cycles(ctx, 16) ;
            }
        } break ;
        case 0x31:
        { // xor reg16/mem16,reg16
            int addr = decodeEA(ctx) ;
            if (is_reg(ctx))
            {
                word left_reg = get_reg16(ctx, addr) ;
                word right_reg = get_reg16(ctx, get_regRM(ctx)) ;
                word result ;
                result.w = left_reg.w ^ right_reg.w ;
                set_reg16(ctx, addr, result) ;
                set_cf(ctx, NO) ;
                set_of(ctx, NO) ;
                is_parity_word(ctx, result) ;
                is_sign_word(ctx, result) ;
                is_zero_word(ctx, result) ;
                set_cycles(ctx, 3) ;
            }
            else
            {
                word left_reg = read_mem_word(ctx, addr) ;
                word right_reg = get_reg16(ctx, get_regRM(ctx)) ;
                word result ;
                result.w = left_reg.w ^ right_reg.w ;
                write_mem_word(ctx, addr, result) ;
                set_cf(ctx, NO) ;
                set_of(ctx, NO) ;
                is_parity_word(ctx, result) ;
                is_sign_word(ctx, result) ;
                is_zero_word(ctx, result) ;
                set_cycles(ctx, 16) ;
            }
        } break ;
        case 0x32:
        { // xor reg8,reg8/mem8
            int addr = decodeEA(ctx) ;
            if (is_reg(ctx))
            {
                byte left_reg = get_reg8(ctx, get_regRM(ctx)) ;
                byte right_reg = get_reg8(ctx, addr) ;
                byte result = left_reg ^ right_reg ;
                set_reg8(ctx, addr, result) ;
                set_cf(ctx, NO) ;
                set_of(ctx, NO) ;
                is_parity_byte(ctx, result) ;
                is_sign_byte(ctx, result) ;
                is_zero_byte(ctx, result) ;
                set_cycles(ctx, 3) ;
            }
            else
            {
                byte left_reg = get_reg8(ctx, get_regRM(ctx)) ;
                byte right_reg = read_mem_byte(ctx, addr) ;
                byte result = left_reg ^ right_reg ;
                set_reg8(ctx, get_regRM(ctx), result) ;
                set_cf(ctx, NO) ;
                set_of(ctx, NO) ;
                is_parity_byte(ctx, result) ;
                is_sign_byte(ctx, result) ;
                is_zero_byte(ctx, result) ;
                set_cycles(ctx, 9) ;
            }
        } break ;
        case 0x33:
        { // xor reg16,reg16/mem16
            int addr = decodeEA(ctx) ;
            if (is_reg(ctx))
            {
                word left_reg = get_reg16(ctx, addr) ;
                word right_reg = get_reg16(ctx, get_regRM(ctx)) ;
                word result ;
                result.w = left_reg.w ^ right_reg.w ;
                set_reg16(ctx, addr, result) ;
                set_cf(ctx, NO) ;
                set_of(ctx, NO) ;
                is_parity_word(ctx, result) ;
                is_sign_word(ctx, result) ;
                is_zero_word(ctx, result) ;
                set_cycles(ctx, 3) ;
            }
            else
            {
                word left_reg = get_reg16(ctx, get_regRM(ctx)) ;
                word right_reg = read_mem_word(ctx, addr) ;
                word result ;
                result.w = left_reg.w ^ right_reg.w ;
                set_reg16(ctx, get_regRM(ctx), result) ;
                set_cf(ctx, NO) ;
                set_of(ctx, NO) ;
                is_parity_word(ctx, result) ;
                is_sign_word(ctx, result) ;
                is_zero_word(ctx, result) ;
                set_cycles(ctx, 9) ;
            }
        } break ;
        case 0x34:
        { // xor al,immed8
            byte left_reg = get_reg8(ctx, AL) ;
            byte right_reg = next_byte(ctx) ;
            byte result = left_reg ^ right_reg ;
            set_reg8(ctx, AL, result) ;
            set_cf(ctx, NO) ;
            set_of(ctx, NO) ;
            is_parity_byte(ctx, result) ;
            is_sign_byte(ctx, result) ;
            is_zero_byte(ctx, result) ;
            set_cycles(ctx, 4) ;
        } break ;
        case 0x35:
        { // xor ax,immed16
            word left_reg = get_reg16(ctx, AX) ;
            word right_reg = next_word(ctx) ;
            word result ;
            result.w = left_reg.w ^ right_reg.w ;
            set_reg16(ctx, AX, result) ;
            set_cf(ctx, NO) ;
            set_of(ctx, NO) ;
            is_parity_word(ctx, result) ;
            is_sign_word(ctx, result) ;
            is_zero_word(ctx, result) ;
            set_cycles(ctx, 4) ;
        } break ;
        case 0x36:
        { // ss - segment override
    
        } break ;
        case 0x37:
        { // aaa
            aaa(ctx) ;
        } break ;
        case 0x38:
        { // cmp reg8/mem8,reg8
            int addr = decodeEA(ctx) ;
            if (is_reg(ctx))
            {
                byte left_reg = get_reg8(ctx, addr) ;
                byte right_reg = get_reg8(ctx, get_regRM(ctx)) ;
                byte result = left_reg - right_reg ;
                byte_cf_sub(ctx, left_reg, right_reg) ;
                byte_of_sub(ctx, left_reg, right_reg)  ;
                byte_af_sub(ctx, left_reg, right_reg) ; 
                is_parity_byte(ctx, result) ;
                is_zero_byte(ctx, result) ;
                is_sign_byte(ctx, result) ;
                set_cycles(ctx, 3) ;
            }
            else
            {
                byte left_reg = read_mem_byte(ctx, addr) ;
                byte right_reg = get_reg8(ctx, get_regRM(ctx)) ;
                byte result = left_reg - right_reg ;
                byte_cf_sub(ctx, left_reg, right_reg) ;
                byte_of_sub(ctx, left_reg, right_reg) ;
                byte_af_sub(ctx, left_reg, right_reg) ; 
                is_parity_byte(ctx, result) ;
                is_zero_byte(ctx, result) ;
                is_sign_byte(ctx, result) ;
                set_cycles(ctx, 9) ;
            }
        } break ;
        case 0x39:
        { // cmp reg16/mem16,reg16
            int addr = decodeEA(ctx) ;
            if (is_reg(ctx))
            {
                word left_reg = get_reg16(ctx, addr) ;
                word right_reg = get_reg16(ctx, get_regRM(ctx)) ;
                word result ;
                result.w = left_reg.w - right_reg.w;
                word_cf_sub(ctx, left_reg, right_reg) ;
                word_of_sub(ctx, left_reg, right_reg) ;
                word_af_sub(ctx, left_reg, right_reg) ; 
                is_parity_word(ctx, result) ;
                is_zero_word(ctx, result) ;
                is_sign_word(ctx, result) ;
                set_cycles(ctx, 3) ;
            }
            else
            {
                word left_reg = read_mem_word(ctx, addr) ;
                word right_reg = get_reg16(ctx, get_regRM(ctx)) ;
                word result ;
                result.w = left_reg.w - right_reg.w;
                word_cf_sub(ctx, left_reg, right_reg) ;
                word_of_sub(ctx, left_reg, right_reg) ;
                word_af_sub(ctx, left_reg, right_reg) ; 
                is_parity_word(ctx, result) ;
                is_zero_word(ctx, result) ;
                is_sign_word(ctx, result) ;
                set_cycles(ctx, 9) ;
            }
        } break ;
        case 0x3A:
        { // cmp reg8,reg8/mem8
            int addr = decodeEA(ctx) ;
            if (is_reg(ctx))
            {
                byte left_reg = get_reg8(ctx, get_regRM(ctx)) ;
                byte right_reg = get_reg8(ctx, addr) ;
                byte result = left_reg - right_reg;
                byte_cf_sub(ctx, left_reg, right_reg) ;
                byte_of_sub(ctx, left_reg, right_reg) ;
                byte_af_sub(ctx, left_reg, right_reg) ; 
                is_parity_byte(ctx, result) ;
                is_zero_byte(ctx, result) ;
                is_sign_byte(ctx, result) ;
                set_cycles(ctx, 3) ;
            }
            else
            {
                byte left_reg = get_reg8(ctx, get_regRM(ctx)) ;
                byte right_reg = read_mem_byte(ctx, addr) ;
                byte result = left_reg - right_reg;
                byte_cf_sub(ctx, left_reg, right_reg) ;
                byte_of_sub(ctx, left_reg, right_reg) ;
                byte_af_sub(ctx, left_reg, right_reg) ; 
                is_parity_byte(ctx, result) ;
                is_zero_byte(ctx, result) ;
                is_sign_byte(ctx, result) ;
                set_cycles(ctx, 9) ;
            }
        } break ;
        case 0x3B:
        { // cmp reg16,reg16/mem16
            int addr = decodeEA(ctx) ;
            if (is_reg(ctx))
            {
                word left_reg = get_reg16(ctx, addr) ;
                word right_reg = get_reg16(ctx, get_regRM(ctx)) ;
                word result ;
                result.w = left_reg.w - right_reg.w;
                word_cf_sub(ctx, left_reg, right_reg) ;
                word_of_sub(ctx, left_reg, right_reg) ;
                word_af_sub(ctx, left_reg, right_reg) ; 
                is_parity_word(ctx, result) ;
                is_zero_word(ctx, result) ;
                is_sign_word(ctx, result) ;
                set_cycles(ctx, 3) ;
            }
            else
            {
                word left_reg = get_reg16(ctx, get_regRM(ctx)) ;
                word right_reg = read_mem_word(ctx, addr) ;
                word result ;
                result.w = left_reg.w - right_reg.w;
                word_cf_sub(ctx, left_reg, right_reg) ;
                word_of_sub(ctx, left_reg, right_reg) ;
                word_af_sub(ctx, left_reg, right_reg) ; 
                is_parity_word(ctx, result) ;
                is_zero_word(ctx, result) ;
                is_sign_word(ctx, result) ;
                set_cycles(ctx, 9) ;
            }
        } break ;
        case 0x3C:
        { // cmp al,immed8
            byte left_reg = get_reg8(ctx, AL) ;
            byte right_reg = next_byte(ctx) ;
            byte result = left_reg - right_reg ;
            byte_cf_sub(ctx, left_reg, right_reg) ;
            byte_of_sub(ctx, left_reg, right_reg) ;
            byte_af_sub(ctx, left_reg, right_reg) ; 
            is_parity_byte(ctx, result) ;
            is_zero_byte(ctx, result) ;
            is_sign_byte(ctx, result) ;
            set_cycles(ctx, 4) ;
        } break ;
        case 0x3D:
        { // cmp ax,immed16
            word left_reg = get_reg16(ctx, AX) ;
            word right_reg = next_word(ctx) ;
            word result ;
            result.w = left_reg.w - right_reg.w;
            word_cf_sub(ctx, left_reg, right_reg) ;
            word_of_sub(ctx, left_reg, right_reg) ;
            word_af_sub(ctx, left_reg, right_reg) ; 
            is_parity_word(ctx, result) ;
            is_zero_word(ctx, result) ;
            is_sign_word(ctx, result) ;
            set_cycles(ctx, 4) ;
        } break ;
        case 0x3E:
        { // ds - segment override
        
        } break ;
        case 0x3F:
        { // ass
            aas(ctx) ;
        } break ;
        case 0x40:
        { // inc ax
            debug("inc ax") ;
            inc_flags(ctx, ctx->ax) ;
            word value ;
            value.w = ctx->ax.w + 1 ;
            set_reg16(ctx, AX, value) ;
            set_cycles(ctx, 3) ;
        } break ;
        case 0x41:
        { // inc cx
            debug("inc cx") ;
            inc_flags(ctx, ctx->cx) ;
            word value ;
            value.w = ctx->cx.w + 1 ;
            set_reg16(ctx, CX, value) ;
            set_cycles(ctx, 3) ;
        } break ;
        case 0x42:
        { // inc dx
            debug("inc dx") ;
            inc_flags(ctx, ctx->dx) ;
            word value ;
            value.w = ctx->dx.w + 1 ;
            set_reg16(ctx, DX, value) ;
            set_cycles(ctx, 3) ;
        } break ;
        case 0x43:
        { // inc bx
            debug("inc bx") ;
            inc_flags(ctx, ctx->bx) ;
            word value ;
            value.w = ctx->bx.w + 1 ;
            set_reg16(ctx, BX, value) ;
            set_cycles(ctx, 3) ;
            
        } break ;
        case 0x44:
        { // inc sp
            debug("inc sp") ;
            inc_flags(ctx, ctx->sp) ;
            word value ;
            value.w = ctx->sp.w + 1 ;
            set_reg16(ctx, SP, value) ;
            set_cycles(ctx, 3) ;
        } break ;
        case 0x45:
        { // inc bp
            debug("inc bp") ;
            inc_flags(ctx, ctx->bp) ;
            word value ;
            value.w = ctx->bp.w + 1 ;
            set_reg16(ctx, BP, value) ;
            set_cycles(ctx, 3) ;
        } break ;
        case 0x46:
        { // inc si
            debug("inc si") ;
            inc_flags(ctx, ctx->si) ;
            word value ;
            value.w = ctx->si.w + 1 ;
            set_reg16(ctx, SI, value) ;
            set_cycles(ctx, 3) ;
        } break ;
        case 0x47:
        { // inc di
            debug("inc di") ;
            inc_flags(ctx, ctx->di) ;
            word value ;
            value.w = ctx->di.w + 1 ;
            set_reg16(ctx, DI, value) ;
            set_cycles(ctx, 3) ;
        } break ;
        case 0x48:
        { // dec ax
            debug("dec ax") ;
            dec_flags(ctx, ctx->ax) ;
            word value ;
            value.w = ctx->ax.w - 1 ;
            set_reg16(ctx, AX, value) ;
            set_cycles(ctx, 3) ;
        } break ;
        case 0x49:
        { // dec cx
            debug("dec cx") ;
            dec_flags(ctx, ctx->cx) ;
            word value ;
            value.w = ctx->cx.w - 1 ;
            set_reg16(ctx, CX, value) ;
            set_cycles(ctx, 3) ;
        } break ;
        case 0x4A:
        { // dec dx
            debug("dec dx") ;
            dec_flags(ctx, ctx->dx) ;
            word value ;
            value.w = ctx->dx.w - 1 ;
            set_reg16(ctx, DX, value) ;
            set_cycles(ctx, 3) ;
        } break ;
        case 0x4B:
        { // dec bx
            debug("dec bx") ;
            dec_flags(ctx, ctx->bx) ;
            word value ;
            value.w = ctx->bx.w - 1  ;
            set_reg16(ctx, BX, value) ;
            set_cycles(ctx, 3) ;
        } break  ;
        case 0x4C:
        { // dec sp
            debug("dec sp") ;
            dec_flags(ctx, ctx->sp)  ;
            word value ;
            value.w = ctx->sp.w - 1 ;
            set_reg16(ctx, SP, value) ;
            set_cycles(ctx, 3) ;
        } break ;
        case 0x4D:
        { // dec bp
            debug("dec bp") ;
            dec_flags(ctx, ctx->bp) ;
            word value ;
            value.w = ctx->bp.w - 1 ;
            set_reg16(ctx, BP, value) ;
            set_cycles(ctx, 3) ;
        } break ;
        case 0x4E:
        { // dec si
            debug("dec si") ;
            dec_flags(ctx, ctx->si) ;
            word value ;
            value.w = ctx->si.w - 1 ;
            set_reg16(ctx, SI, value) ;
            set_cycles(ctx, 3) ;
        } break ;
        case 0x4F:
        { // dec di
            debug("dec di") ;
            dec_flags(ctx, ctx->di) ;
            word value ;
            value.w = ctx->di.w - 1 ;
            set_reg16(ctx, DI, value) ;
            set_cycles(ctx, 3) ;
        } break ;
        case 0x50:
        { // push ax
            debug("push ax") ;
            ctx->sp.w = ctx->sp.w - 2 ;
            write_mem_word(ctx, (ctx->ss.w << 4) + ctx->sp.w, ctx->ax) ;
            set_cycles(ctx, 11) ;
        } break ;
        case 0x51:
        { // push cx
            debug("push cx") ;
            ctx->sp.w = ctx->sp.w - 2 ;
            write_mem_word(ctx, (ctx->ss.w << 4) + ctx->sp.w, ctx->cx) ;
            set_cycles(ctx, 11) ;
        } break ;
        case 0x52:
        { // push dx
            debug("push dx") ;
            ctx->sp.w = ctx->sp.w - 2 ;
            write_mem_word(ctx, (ctx->ss.w << 4) + ctx->sp.w, ctx->dx) ;
            set_cycles(ctx, 11) ;
        } break ;
        case 0x53:
        { // push bx
            debug("push bx") ;
            ctx->sp.w = ctx->sp.w - 2 ;
            write_mem_word(ctx, (ctx->ss.w << 4) + ctx->sp.w, ctx->bx) ;
            set_cycles(ctx, 11) ;
        } break ;
        case 0x54:
        { // push sp
            debug("push sp") ;
            ctx->sp.w = ctx->sp.w - 2 ;
            write_mem_word(ctx, (ctx->ss.w << 4) + ctx->sp.w, ctx->sp) ;
            set_cycles(ctx, 11) ;
        } break ;
        case 0x55:
        { // push bp
            debug("push bp") ;
            ctx->sp.w = ctx->sp.w - 2 ;
            write_mem_word(ctx, (ctx->ss.w << 4) + ctx->sp.w, ctx->bp) ;
            set_cycles(ctx, 11) ;
        } break ;
        case 0x56:
        { // push si
            debug("push si") ;
            ctx->sp.w = ctx->sp.w - 2 ;
            write_mem_word(ctx, (ctx->ss.w << 4) + ctx->sp.w, ctx->si) ;
            set_cycles(ctx, 11) ;
        } break ;
        case 0x57:
        { // push di
            debug("push di") ;
            ctx->sp.w = ctx->sp.w - 2 ;
            write_mem_word(ctx, (ctx->ss.w << 4) + ctx->sp.w, ctx->di) ;
            set_cycles(ctx, 11) ;
        } break ;
        case 0x58:
        { // pop ax
            debug("pop ax") ;
            ctx->ax = read_mem_word(ctx, (ctx->ss.w << 4) + ctx->sp.w) ;
            ctx->sp.w = ctx->sp.w + 2 ;
            set_cycles(ctx, 8) ;
        } break ;
        case 0x59:
        { // pop cx
            debug("pop cx") ;
            ctx->cx = read_mem_word(ctx, (ctx->ss.w << 4) + ctx->sp.w) ;
            ctx->sp.w = ctx->sp.w + 2 ;
            set_cycles(ctx, 8) ;
        } break ;
        case 0x5A:
        { // pop dx
            debug("pop dx") ;
            ctx->dx = read_mem_word(ctx, (ctx->ss.w << 4) + ctx->sp.w) ;
            ctx->sp.w = ctx->sp.w + 2 ;
            set_cycles(ctx, 8) ;
        } break ;
        case 0x5B:
        { // pop bx
            debug("pop bx") ;
            ctx->bx = read_mem_word(ctx, (ctx->ss.w << 4) + ctx->sp.w) ;
            ctx->sp.w = ctx->sp.w + 2 ;
            set_cycles(ctx, 8) ;
        } break ;
        case 0x5C:
        { // pop sp
            debug("pop sp") ;
            ctx->sp = read_mem_word(ctx, (ctx->ss.w << 4) + ctx->sp.w) ;
            ctx->sp.w = ctx->sp.w + 2 ;
            set_cycles(ctx, 8) ;
        } break ;
        case 0x5D:
        { // pop bp
            debug("pop bp") ;
            ctx->bp = read_mem_word(ctx, (ctx->ss.w << 4) + ctx->sp.w) ;
            ctx->sp.w = ctx->sp.w + 2 ;
            set_cycles(ctx, 8) ;
        } break ;
        case 0x5E:
        { // pop si
            debug("pop si") ;
            ctx->si = read_mem_word(ctx, (ctx->ss.w << 4) + ctx->sp.w) ;
            ctx->sp.w = ctx->sp.w + 2 ;
            set_cycles(ctx, 8) ;
        } break ;
        case 0x5F:
        { // pop di
            debug("pop di") ;
            ctx->di = read_mem_word(ctx, (ctx->ss.w << 4) + ctx->sp.w) ;
            ctx->sp.w = ctx->sp.w + 2 ;
            set_cycles(ctx, 8) ;
        } break ;
        case 0x70:
        { // jo label
            debug("jo") ;
            signed char disp8 = (signed)next_byte(ctx) ;
            if (get_of(ctx) == YES)
            {
                ctx->ip.w = ctx->ip.w + disp8 ;
                set_cycles(ctx, 16) ;
            }
            else set_cycles(ctx, 4) ;
        } break ;
        case 0x71:
        { // jno label
            debug("jno") ;
            signed char disp8 = (signed)next_byte(ctx) ;
            if (get_of(ctx) == NO)
            {
                ctx->ip.w = ctx->ip.w + disp8 ;
                set_cycles(ctx, 16) ;
            } else set_cycles(ctx, 4) ;
        } break ;
        case 0x72:
        { // jb/jnae/jc label
            debug("jb/jnae/jc label") ;
            signed char disp8 = (signed)next_byte(ctx) ;
            if (get_cf(ctx) == YES)
            {
                ctx->ip.w = ctx->ip.w + disp8 ;
                set_cycles(ctx, 16) ;
            } else set_cycles(ctx, 4) ;
        } break ;
        case 0x73:
        { // jnb/jae/jnc label
            debug("jnb/jae/jnc label") ;
            signed char disp8 = (signed)next_byte(ctx) ;
            if (get_cf(ctx) == NO)
            {
                ctx->ip.w = ctx->ip.w + disp8 ;
                set_cycles(ctx, 16) ;
            } else set_cycles(ctx, 4) ;
        } break ;
        case 0x74:
        { // je/jz label
            debug("je/jz label") ;
            signed char disp8 = (signed)next_byte(ctx) ;
            if (get_zf(ctx) == YES)
            {
                ctx->ip.w = ctx->ip.w + disp8 ;
                set_cycles(ctx, 16) ;
            } else set_cycles(ctx, 4) ;
        } break ;
        case 0x75:
        { // jne/jnz label
            debug("jne/jnz label") ;
            signed char disp8 = (signed)next_byte(ctx) ;
            if (get_zf(ctx) == NO)
            {
                ctx->ip.w = ctx->ip.w + disp8 ;
                set_cycles(ctx, 16) ;
            } else set_cycles(ctx, 4) ;
        } break ;
        case 0x76:
        { // jbe/jna label
            debug("jbe/jna label") ;
            signed char disp8 = (signed)next_byte(ctx) ;
            if (get_cf(ctx) == YES || get_zf(ctx) == YES)
            {
                ctx->ip.w = ctx->ip.w + disp8 ;
                set_cycles(ctx, 16) ;
            } else set_cycles(ctx, 4) ;
        } break ;
        case 0x77:
        { // jnbe/ja label
            debug("jnbe/ja label") ;
            signed char disp8 = (signed)next_byte(ctx) ;
            if (get_cf(ctx) == NO && get_zf(ctx) == NO)
            {
                ctx->ip.w = ctx->ip.w + disp8 ;
                set_cycles(ctx, 16) ;
            } else set_cycles(ctx, 4) ;
        } break ;
        case 0x78:
        { // js label
            debug("js labael") ;
            signed char disp8 = (signed)next_byte(ctx) ;
            if (get_sf(ctx) == YES)
            {
                ctx->ip.w = ctx->ip.w + disp8 ;
                set_cycles(ctx, 16) ;
            } else set_cycles(ctx, 4) ;
        } break ;
        case 0x79:
        { // jns label
            debug("jns label") ;
            signed char disp8 = (signed)next_byte(ctx) ;
            if (get_sf(ctx) == NO)
            {
                ctx->ip.w = ctx->ip.w + disp8 ;
                set_cycles(ctx, 16) ;
            } else set_cycles(ctx, 4) ;
        } break ;
        case 0x7A:
        { // jp/jpe label
            debug("jp/jpe label") ;
            signed char disp8 = (signed)next_byte(ctx) ;
            if (get_pf(ctx) == YES)
            {
                ctx->ip.w = ctx->ip.w + disp8 ;
                set_cycles(ctx, 16) ;
            } else set_cycles(ctx, 4) ;
        } break ;
        case 0x7B:
        { // jnp/jpo label
            debug("jnp/jpo label") ;
            signed char disp8 = (signed)next_byte(ctx) ;
            if (get_pf(ctx) == NO)
            {
                ctx->ip.w = ctx->ip.w + disp8 ;
                set_cycles(ctx, 16) ;
            } else set_cycles(ctx, 4) ;
        } break ;
        case 0x7C:
        { // jl/jnge label
            debug("jl/jnge label") ;
            signed char disp8 = (signed)next_byte(ctx) ;
            if (get_sf(ctx) != get_of(ctx))
            {
                ctx->ip.w = ctx->ip.w + disp8 ;
                set_cycles(ctx, 16) ;
            } else set_cycles(ctx, 4) ;
        } break ;
        case 0x7D:
        { // jnl/jge label
            debug("jnl/jge label");
            signed char disp8 = (signed)next_byte(ctx) ;
            if (get_sf(ctx) == get_of(ctx))
            {
                ctx->ip.w = ctx->ip.w + disp8 ;
                set_cycles(ctx, 16) ;
            } else set_cycles(ctx, 4) ;
        } break ;
        case 0x7E:
        { // jle/jng label
            debug("jle/jng label") ;
            signed char disp8 = (signed)next_byte(ctx) ;
            if ((get_sf(ctx) != get_of(ctx)) || get_zf(ctx) == YES)
            {
                ctx->ip.w = ctx->ip.w + disp8 ;
                set_cycles(ctx, 16) ;
            } else set_cycles(ctx, 4) ;
        } break ;
        case 0x7F:
        { // jnle/jg label
            debug("jnle/jg label") ;
            signed char disp8 = (signed)next_byte(ctx) ;
            if ((get_sf(ctx) == get_of(ctx)) || get_zf(ctx) == NO)
            {
                ctx->ip.w = ctx->ip.w + disp8 ;
                set_cycles(ctx, 16) ;
            } else set_cycles(ctx, 4) ;
        } break ;
        case 0x80:
        {
            byte op = ((read_byte(ctx) & 0x38) >> 3) ;
            switch (op)
            {
                case 0x00:
                { // add reg8/mem8,immed8
                    int addr = decodeEA(ctx) ;
                    debug("add reg8/mem8,immed8") ;
                    if (is_reg(ctx))
                    {
                        byte left_reg = get_reg8(ctx, addr) ;
                        byte right_reg = next_byte(ctx) ;
                        byte result = left_reg + right_reg ;
                        set_reg8(ctx, addr, result) ;
                        set_cf_byte(ctx, left_reg+right_reg) ;
                        set_of_byte(ctx, left_reg, right_reg, result)  ;
                        if (((left_reg & 0x0F) + (right_reg & 0x0F)) & 0x10) set_af(ctx, YES) ;
                        else set_af(ctx, NO) ;
                        is_parity_byte(ctx, result) ;
                        is_zero_byte(ctx, result) ;
                        is_sign_byte(ctx, result) ;
                        set_cycles(ctx, 4) ;
                    }
                    else
                    {
                        byte left_reg = read_mem_byte(ctx, addr) ;
                        byte right_reg = next_byte(ctx) ;
                        byte result = left_reg + right_reg ;
                        write_mem_byte(ctx, addr, result) ;
                        set_cf_byte(ctx, left_reg+right_reg) ;
                        set_of_byte(ctx, left_reg, right_reg, result)  ;
                        if (((left_reg & 0x0F) + (right_reg & 0x0F)) & 0x10) set_af(ctx, YES) ;
                        else set_af(ctx, NO) ;
                        is_parity_byte(ctx, result) ;
                        is_zero_byte(ctx, result) ;
                        is_sign_byte(ctx, result) ;
                        set_cycles(ctx, 17) ;
                    }
                } break ;
                case 0x01:
                { // or reg8/mem8,immed8
                    int addr = decodeEA(ctx) ;
                    debug("or reg8/mem8,immed8") ;
                    if (is_reg(ctx))
                    {
                        byte left_reg = get_reg8(ctx, addr) ;
                        byte right_reg = next_byte(ctx) ;
                        byte result = left_reg | right_reg ;
                        set_reg8(ctx, addr, result) ;
                        set_cf(ctx, NO) ;
                        set_of(ctx, NO) ;
                        is_parity_byte(ctx, result) ;
                        is_sign_byte(ctx, result) ;
                        is_zero_byte(ctx, result) ;
                        set_cycles(ctx, 4) ;
                    }
                    else
                    {
                        byte left_reg = read_mem_byte(ctx, addr) ;
                        byte right_reg = next_byte(ctx) ;
                        byte result = left_reg | right_reg ;
                        write_mem_byte(ctx, addr, result) ;
                        set_cf(ctx, NO) ;
                        set_of(ctx, NO) ;
                        is_parity_byte(ctx, result) ;
                        is_sign_byte(ctx, result) ;
                        is_zero_byte(ctx, result) ;
                        set_cycles(ctx, 17) ;
                    }
                } break ;
                case 0x02:
                { // adc reg8/mem8,immed8
                    int addr = decodeEA(ctx) ;
                    debug("adc reg8/mem8,immed8") ;
                    if (is_reg(ctx))
                    {
                        byte left_reg = get_reg8(ctx, addr) ;
                        byte right_reg = next_byte(ctx) ;
                        byte result = left_reg + right_reg + get_cf(ctx) ;
                        set_reg8(ctx, addr, result) ;
                        set_of_byte(ctx, left_reg, right_reg+get_cf(ctx), result)  ;
                        if (((left_reg & 0x0F) + (right_reg & 0x0F) + get_cf(ctx)) & 0x10) set_af(ctx, YES) ;
                        else set_af(ctx, NO) ;
                        set_cf_byte(ctx, left_reg+right_reg+get_cf(ctx)) ;
                        is_parity_byte(ctx, result) ;
                        is_zero_byte(ctx, result) ;
                        is_sign_byte(ctx, result) ;
                        set_cycles(ctx, 4) ;
                    }
                    else
                    {
                        byte left_reg = read_mem_byte(ctx, addr) ;
                        byte right_reg = next_byte(ctx) ;
                        byte result = left_reg + right_reg + get_cf(ctx) ;
                        write_mem_byte(ctx, addr, result) ;
                        set_of_byte(ctx, left_reg, right_reg+get_cf(ctx), result)  ;
                        if (((left_reg & 0x0F) + (right_reg & 0x0F) + get_cf(ctx)) & 0x10) set_af(ctx, YES) ;
                        else set_af(ctx, NO) ;
                        set_cf_byte(ctx, left_reg+right_reg+get_cf(ctx)) ;
                        is_parity_byte(ctx, result) ;
                        is_zero_byte(ctx, result) ;
                        is_sign_byte(ctx, result) ;
                        set_cycles(ctx, 17) ;
                    }
                } break ;
                case 0x03:
                { // sbb reg8/mem8,immed8
                    int addr = decodeEA(ctx) ;
                    debug("sbb reg8/mem8,immed8") ;
                    if (is_reg(ctx))
                    {
                        byte left_reg = get_reg8(ctx, addr) ;
                        byte right_reg = next_byte(ctx) ;
                        byte result = left_reg - (right_reg + get_cf(ctx)) ;
                        set_reg8(ctx, addr, result) ;
                        sbb_of_byte(ctx, left_reg, right_reg) ;
                        sbb_cf_byte(ctx, left_reg, right_reg) ;
                        sbb_af_byte(ctx, left_reg, right_reg) ;
                        is_parity_byte(ctx, result) ;
                        is_zero_byte(ctx, result) ;
                        is_sign_byte(ctx, result) ;
                        set_cycles(ctx, 4) ;
                    }
                    else
                    {
                        byte left_reg = read_mem_byte(ctx, addr) ;
                        byte right_reg = next_byte(ctx) ;
                        byte result = left_reg - (right_reg + get_cf(ctx)) ;
                        write_mem_byte(ctx, addr, result) ;
                        sbb_of_byte(ctx, left_reg, right_reg) ;
                        sbb_cf_byte(ctx, left_reg, right_reg) ;
                        sbb_af_byte(ctx, left_reg, right_reg) ;
                        is_parity_byte(ctx, result) ;
                        is_zero_byte(ctx, result) ;
                        is_sign_byte(ctx, result) ;
                        set_cycles(ctx, 17) ;
                    }
                } break ;
                case 0x04:
                { // and reg8/mem8,immed8
                    int addr = decodeEA(ctx) ;
                    debug("and reg8/mem8,immed8") ;
                    if (is_reg(ctx))
                    {
                        byte left_reg = get_reg8(ctx, addr) ;
                        byte right_reg = next_byte(ctx) ;
                        byte result = left_reg & right_reg ;
                        set_reg8(ctx, addr, result) ;
                        set_cf(ctx, NO) ;
                        set_of(ctx, NO) ;
                        set_cycles(ctx, 4) ;
                    }
                    else
                    {
                        byte left_reg = read_mem_byte(ctx, addr) ;
                        byte right_reg = next_byte(ctx) ;
                        byte result = left_reg & right_reg ;
                        write_mem_byte(ctx, addr, result) ;
                        set_cf(ctx, NO) ;
                        set_of(ctx, NO) ;
                        set_cycles(ctx, 17) ;
                    }
                } break ;
                case 0x05:
                { // sub reg8/mem8,immed8
                    int addr = decodeEA(ctx) ;
                    if (is_reg(ctx))
                    {
                        byte left_reg = get_reg8(ctx, addr) ;
                        byte right_reg = next_byte(ctx) ;
                        byte result = left_reg - right_reg ;
                        set_reg8(ctx, addr, result) ;
                        byte_cf_sub(ctx, left_reg, right_reg) ;
                        byte_of_sub(ctx, left_reg, right_reg) ;
                        byte_af_sub(ctx, left_reg, right_reg) ;
                        is_parity_byte(ctx, result) ;
                        is_zero_byte(ctx, result) ;
                        is_sign_byte(ctx, result) ;
                        set_cycles(ctx, 4) ;
                    }
                    else
                    {
                        byte left_reg = read_mem_byte(ctx, addr) ;
                        byte right_reg = next_byte(ctx) ;
                        byte result = left_reg - right_reg ;
                        write_mem_byte(ctx, addr, result) ;
                        byte_cf_sub(ctx, left_reg, right_reg) ;
                        byte_of_sub(ctx, left_reg, right_reg) ;
                        byte_af_sub(ctx, left_reg, right_reg) ;
                        is_parity_byte(ctx, result) ;
                        is_zero_byte(ctx, result) ;
                        is_sign_byte(ctx, result) ;
                        set_cycles(ctx, 17) ;
                    }
                } break ;
                case 0x06:
                { // xor reg8/mem8,immed8
                    debug("xor reg8/mem8,immed8") ;
                    int addr = decodeEA(ctx) ;
                    if (is_reg(ctx))
                    {
                        byte left_reg = get_reg8(ctx, addr) ;
                        byte right_reg = next_byte(ctx) ;
                        byte result = left_reg ^ right_reg ;
                        set_reg8(ctx, addr, result) ;
                        set_cf(ctx, NO) ;
                        set_of(ctx, NO) ;
                        is_parity_byte(ctx, result) ;
                        is_sign_byte(ctx, result) ;
                        is_zero_byte(ctx, result) ;
                        set_cycles(ctx, 4) ;
                    }
                    else
                    {
                        byte left_reg = read_mem_byte(ctx, addr) ;
                        byte right_reg = next_byte(ctx) ;
                        byte result = left_reg ^ right_reg ;
                        write_mem_byte(ctx, addr, result) ;
                        set_cf(ctx, NO) ;
                        set_of(ctx, NO) ;
                        is_parity_byte(ctx, result) ;
                        is_sign_byte(ctx, result) ;
                        is_zero_byte(ctx, result) ;
                        set_cycles(ctx, 17) ;
                    }
                } break ;
                case 0x07:
                { // cmp reg8/mem8,immed8
                    debug("cmp reg8/mem8,immed8") ;
                    int addr = decodeEA(ctx) ;
                    if (is_reg(ctx))
                    {
                        byte left_reg = get_reg8(ctx, addr) ;
                        byte right_reg = next_byte(ctx) ;
                        byte result = left_reg - right_reg ;
                        byte_cf_sub(ctx, left_reg, right_reg) ;
                        byte_of_sub(ctx, left_reg, right_reg)  ;
                        byte_af_sub(ctx, left_reg, right_reg) ;
                        is_parity_byte(ctx, result) ;
                        is_zero_byte(ctx, result) ;
                        is_sign_byte(ctx, result) ;
                        set_cycles(ctx, 4) ;
                    }
                    else
                    {
                        byte left_reg = read_mem_byte(ctx, addr) ;
                        byte right_reg = next_byte(ctx) ;
                        byte result = left_reg - right_reg ;
                        byte_cf_sub(ctx, left_reg, right_reg) ;
                        byte_of_sub(ctx, left_reg, right_reg)  ;
                        byte_af_sub(ctx, left_reg, right_reg) ;
                        is_parity_byte(ctx, result) ;
                        is_zero_byte(ctx, result) ;
                        is_sign_byte(ctx, result) ;
                        set_cycles(ctx, 10) ;
                    }
                } break ;
            }
        } break ;
        case 0x81:
        {
            byte op = ((read_byte(ctx) & 0x38) >> 3) ;
            switch (op)
            {
                case 0x00:
                { // add reg16/mem16,immed16
                    debug("add reg16/mem16,immed16") ;
                    int addr = decodeEA(ctx) ;
                    if (is_reg(ctx))
                    {
                        word left_reg = get_reg16(ctx, addr) ;
                        word right_reg = next_word(ctx) ;
                        word result ;
                        result.w = left_reg.w + right_reg.w ;
                        set_reg16(ctx, addr, result) ;
                        set_cf_word(ctx, left_reg.w + right_reg.w) ;
                        if (((left_reg.w & 0x0F) + (right_reg.w & 0x0F)) & 0x10) set_af(ctx, YES) ;
                        else set_af(ctx, NO) ;
                        set_of_word(ctx, right_reg, left_reg, result) ;
                        is_parity_word(ctx, result) ;
                        is_zero_word(ctx, result) ;
                        is_sign_word(ctx, result) ;
                        set_cycles(ctx, 4) ;
                    }
                    else
                    {
                        word left_reg = read_mem_word(ctx, addr) ;
                        word right_reg = next_word(ctx) ;
                        word result ;
                        result.w = left_reg.w + right_reg.w ;
                        write_mem_word(ctx, addr, result) ;
                        set_cf_word(ctx, left_reg.w + right_reg.w) ;
                        if (((left_reg.w & 0x0F) + (right_reg.w & 0x0F)) & 0x10) set_af(ctx, YES) ;
                        else set_af(ctx, NO) ;
                        set_of_word(ctx, right_reg, left_reg, result) ;
                        is_parity_word(ctx, result) ;
                        is_zero_word(ctx, result) ;
                        is_sign_word(ctx, result) ;
                        set_cycles(ctx, 17) ;
                    }
                } break ;
                case 0x01:
                { // or reg16/mem16,immed16
                    debug("or reg16/mem16,immed16") ;
                    int addr = decodeEA(ctx) ;
                    if (is_reg(ctx))
                    {
                        word left_reg = get_reg16(ctx, addr) ;
                        word right_reg = next_word(ctx) ;
                        word result ;
                        result.w = left_reg.w | right_reg.w ;
                        set_reg16(ctx, addr, result) ;
                        set_cf(ctx, NO) ;
                        set_of(ctx, NO) ;
                        is_parity_word(ctx, result) ;
                        is_sign_word(ctx, result) ;
                        is_zero_word(ctx, result) ;
                        set_cycles(ctx, 4) ;
                    }
                    else
                    {
                        word left_reg = read_mem_word(ctx, addr) ;
                        word right_reg = next_word(ctx) ;
                        word result ;
                        result.w = left_reg.w | right_reg.w ;
                        write_mem_word(ctx, addr, result) ;
                        set_cf(ctx, NO) ;
                        set_of(ctx, NO) ;
                        is_parity_word(ctx, result) ;
                        is_sign_word(ctx, result) ;
                        is_zero_word(ctx, result) ;
                        set_cycles(ctx, 17) ;
                    }
                } break ;
                case 0x02:
                { // adc reg16/mem16,immed16
                    debug("adc reg16/mem16,immed16") ;
                    int addr = decodeEA(ctx) ;
                    if (is_reg(ctx))
                    {
                        word left_reg = get_reg16(ctx, addr) ;
                        word right_reg = next_word(ctx) ;
                        word result ;
                        result.w = left_reg.w + right_reg.w + get_cf(ctx) ;
                        set_reg16(ctx, addr, result) ;
                        word second_op ;
                        second_op.w = right_reg.w + get_cf(ctx) ;
                        set_of_word(ctx, left_reg, second_op, result) ;
                        word_af_adc(ctx, left_reg, right_reg) ;
                        set_cf_word(ctx, left_reg.w+right_reg.w+get_cf(ctx)) ;
                        is_parity_word(ctx, result) ;
                        is_zero_word(ctx, result) ;
                        is_sign_word(ctx, result) ;
                        set_cycles(ctx, 4) ;
                    }
                    else
                    {
                        word left_reg = read_mem_word(ctx, addr) ;
                        word right_reg = next_word(ctx) ;
                        word result ;
                        result.w = left_reg.w + right_reg.w + get_cf(ctx) ;
                        write_mem_word(ctx, addr, result) ;
                        word second_op ;
                        second_op.w = right_reg.w + get_cf(ctx) ;
                        set_of_word(ctx, left_reg, second_op, result) ;
                        word_af_                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                         (ctx, left_reg, right_reg) ;
                        set_cf_word(ctx, left_reg.w+right_reg.w+get_cf(ctx)) ;
                        is_parity_word(ctx, result) ;
                        is_zero_word(ctx, result) ;
                        is_sign_word(ctx, result) ;
                        set_cycles(ctx, 17) ;
                    }

                } break ;
                case 0x03:
                { // sbb reg16/mem16,immed16
                    debug("sbb reg16/mem16,immed16") ;
                    int addr = decodeEA(ctx) ;
                    if (is_reg(ctx))
                    {
                        word left_reg = get_reg16(ctx, addr) ;
                        word right_reg = next_word(ctx) ;
                        word result ;
                        result.w = left_reg.w - (right_reg.w + get_cf(ctx)) ;
                        set_reg16(ctx, addr, result) ;
                        sbb_of_word(ctx, left_reg, right_reg) ;
                        sbb_cf_word(ctx, left_reg, right_reg) ;
                        sbb_af_word(ctx, left_reg, right_reg) ;
                        is_parity_word(ctx, result) ;
                        is_zero_word(ctx, result) ;
                        is_sign_word(ctx, result) ;
                        set_cycles(ctx, 4) ;
                    }
                    else
                    {
                        word left_reg = read_mem_word(ctx, addr) ;
                        word right_reg = next_word(ctx) ;
                        word result ;
                        result.w = left_reg.w - (right_reg.w + get_cf(ctx));
                        write_mem_word(ctx, addr, result) ;
                        sbb_of_word(ctx, left_reg, right_reg) ;
                        sbb_cf_word(ctx, left_reg, right_reg) ;
                        sbb_af_word(ctx, left_reg, right_reg) ;
                        is_parity_word(ctx, result) ;
                        is_zero_word(ctx, result) ;
                        is_sign_word(ctx, result) ;
                        set_cycles(ctx, 17) ;
                    }

                } break ;
                case 0x04:
                { // and reg16/mem16,immed16
                    debug("and reg16/mem16,immed16") ;
                    int addr = decodeEA(ctx) ;
                    if (is_reg(ctx))
                    {
                        word left_reg = get_reg16(ctx, addr) ;
                        word right_reg = next_word(ctx) ;
                        word result ;
                        result.w = left_reg.w & right_reg.w ;
                        set_reg16(ctx, addr, result) ;
                        set_cf(ctx, NO) ;
                        set_of(ctx, NO) ;
                        set_cycles(ctx, 4) ;
                    }
                    else
                    {
                        word left_reg = read_mem_word(ctx, addr) ;
                        word right_reg = next_word(ctx) ;
                        word result ;
                        result.w = left_reg.w & right_reg.w ;
                        write_mem_word(ctx, addr, result) ;
                        set_cf(ctx, NO) ;
                        set_of(ctx, NO) ;
                        set_cycles(ctx, 17) ;
                    }
                } break ;
                case 0x05:
                { // sub reg16/mem16,immed16
                    debug("sub reg16/mem16,immed16") ;
                    int addr = decodeEA(ctx) ;
                    if (is_reg(ctx))
                    {
                        word left_reg = get_reg16(ctx, addr) ;
                        word right_reg = next_word(ctx) ;
                        word result ;
                        result.w = left_reg.w - right_reg.w;
                        set_reg16(ctx, addr, result) ;
                        word_cf_sub(ctx, left_reg, right_reg) ;
                        word_of_sub(ctx, left_reg, right_reg) ;
                        word_af_sub(ctx, left_reg, right_reg) ;
                        is_parity_word(ctx, result) ;
                        is_zero_word(ctx, result) ;
                        is_sign_word(ctx, result) ;
                        set_cycles(ctx, 4) ;
                    }
                    else
                    {
                        word left_reg = read_mem_word(ctx, addr) ;
                        word right_reg = next_word(ctx) ;
                        word result ;
                        result.w = left_reg.w - right_reg.w;
                        write_mem_word(ctx, addr, result) ;
                        word_cf_sub(ctx, left_reg, right_reg) ;
                        word_of_sub(ctx, left_reg, right_reg) ;
                        word_af_sub(ctx, left_reg, right_reg) ;
                        is_parity_word(ctx, result) ;
                        is_zero_word(ctx, result) ;
                        is_sign_word(ctx, result) ;
                        set_cycles(ctx, 17) ;
                    }
                } break ;
                case 0x06:
                { // xor reg16/mem16,immed16
                    debug("xor reg16/mem16,immed16") ;
                    int addr = decodeEA(ctx) ;
                    if (is_reg(ctx))
                    {
                        word left_reg = get_reg16(ctx, addr) ;
                        word right_reg = next_word(ctx) ;
                        word result ;
                        result.w = left_reg.w ^ right_reg.w ;
                        set_reg16(ctx, addr, result) ;
                        set_cf(ctx, NO) ;
                        set_of(ctx, NO) ;
                        is_parity_word(ctx, result) ;
                        is_sign_word(ctx, result) ;
                        is_zero_word(ctx, result) ;
                        set_cycles(ctx, 4) ;
                    }
                    else
                    {
                        word left_reg = read_mem_word(ctx, addr) ;
                        word right_reg = next_word(ctx) ;
                        word result ;
                        result.w = left_reg.w ^ right_reg.w ;
                        write_mem_word(ctx, addr, result) ;
                        set_cf(ctx, NO) ;
                        set_of(ctx, NO) ;
                        is_parity_word(ctx, result) ;
                        is_sign_word(ctx, result) ;
                        is_zero_word(ctx, result) ;
                        set_cycles(ctx, 17) ;
                    }
                } break ;
                case 0x07:
                { // cmp reg16/mem16,immed16
                    debug("cmp reg16/mem16,immed16") ;
                    int addr = decodeEA(ctx) ;
                    if (is_reg(ctx))
                    {
                        word left_reg = get_reg16(ctx, addr) ;
                        word right_reg = next_word(ctx) ;
                        word result ;
                        result.w = left_reg.w - right_reg.w;
                        word_cf_sub(ctx, left_reg, right_reg) ;
                        word_of_sub(ctx, left_reg, right_reg) ;
                        word_af_sub(ctx, left_reg, right_reg) ;
                        is_parity_word(ctx, result) ;
                        is_zero_word(ctx, result) ;
                        is_sign_word(ctx, result) ;
                        set_cycles(ctx, 4) ;
                    }
                    else
                    {
                        word left_reg = read_mem_word(ctx, addr) ;
                        word right_reg = next_word(ctx) ;
                        word result ;
                        result.w = left_reg.w - right_reg.w;
                        word_cf_sub(ctx, left_reg, right_reg) ;
                        word_of_sub(ctx, left_reg, right_reg) ;
                        word_af_sub(ctx, left_reg, right_reg) ;
                        is_parity_word(ctx, result) ;
                        is_zero_word(ctx, result) ;
                        is_sign_word(ctx, result) ;
                        set_cycles(ctx, 10) ;
                    }
                } break ;
            }
        } break ;
    }
}
