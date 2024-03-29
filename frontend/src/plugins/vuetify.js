/**
 * plugins/vuetify.js
 *
 * Framework documentation: https://vuetifyjs.com`
 */

// Styles
import '@mdi/font/css/materialdesignicons.css'
import 'vuetify/styles'

// Composables
import { createVuetify } from 'vuetify'

const lightMode = {
  dark: false,
  colors: {
    primary : "#00897B",
    onPrimary : "#000000",
    primaryContainer : "#00838F",
    onPrimaryContainer : "#001A42",
    secondary : "#00E5FF",
    onSecondary : "#000000",
    secondaryContainer : "#00838F",
    onSecondaryContainer : "#001A42",
    tertiary : "#4DD0E1",
    onTertiary : "#000000",
    tertiaryContainer : "#00838F",
    onTertiaryContainer : "#001A42",
    error : "#BA1A1A",
    errorContainer : "#FFDAD6",
    onError : "#FFFFFF",
    onErrorContainer : "#410002",
    background : "#FFFFFF", // #FEFBFF
    onBackground : "#F5F5F5",
    surface : "#F5F5F5", // #F0F0F0  , #FFFBFE
    onSurface : "#1B1B1F",
    surfaceVariant : "#E1E2EC",
    onSurfaceVariant : "#44474F",
    outline : "#75777F",
    inverseOnSurface : "#F2F0F4",
    inverseSurface : "#303034",
    inversePrimary : "#AEC6FF",
    shadow : "#000000",
    surfaceTint : "#335CA8",
    outlineVariant : "#C5C6D0",
    scrim : "#000000"
  },
}

const darkMode = {
  dark: true,
  colors: {
    primary : "#00BCD4",
    onPrimary : "#FFFFFF",
    primaryContainer : "#00838F",
    onPrimaryContainer : "#001A42",
    secondary : "#00E5FF",
    onSecondary : "#000000",
    secondaryContainer : "#00838F",
    onSecondaryContainer : "#001A42",
    tertiary : "#4DD0E1",
    onTertiary : "#000000",
    tertiaryContainer : "#00838F",
    onTertiaryContainer : "#001A42",
    error : "#FFB4AB",
    errorContainer : "#93000A",
    onError : "#690005",
    onErrorContainer : "#FFDAD6",
    background : "#121212",//"#152028", //"#232B32",//"#121212", // "#1B1B1F"
    onBackground : "#E3E2E6",
    surface : "#F5F5F5",
    onSurface : "#E3E2E6",
    surfaceVariant : "#44474F",
    onSurfaceVariant : "#C5C6D0",
    outline : "#8E9099",
    inverseOnSurface : "#1B1B1F",
    inverseSurface : "#E3E2E6",
    inversePrimary : "#335CA8",
    shadow : "#000000",
    surfaceTint : "#AEC6FF",
    outlineVariant : "#44474F",
    scrim : "#000000"
  },
}

// https://vuetifyjs.com/en/introduction/why-vuetify/#feature-guides
export default createVuetify({
  theme: {
    defaultTheme: 'lightMode',
    themes: {
      lightMode,
      darkMode 
    },
  } 
})
