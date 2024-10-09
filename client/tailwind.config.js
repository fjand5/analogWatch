/** @type {import('tailwindcss').Config} */
export default {
  content: ['./index.html', './src/**/*.{vue,js,ts,jsx,tsx}'],
  theme: {
    extend: {
      keyframes: {
        gradient: {
          '0%': {
            'background-position': '200% 0%'
          },
          '100%': {
            'background-position': '0% 0%'
          }
        }
      },
      animation: {
        'gradient': 'gradient 5s linear infinite',
      },
      colors: {
        dark: {
          100: '#212121',
          200: '#424242',
          300: '#FFF07A',
          400: '#FFE0B2',
          500: '#ECEFF1'
        }
      }
    }
  },
  plugins: []
}
