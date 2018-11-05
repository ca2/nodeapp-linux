#pragma once


namespace multimedia
{


   namespace audio_mixer_mmsystem
   {


      class CLASS_DECL_AUDIO_MIXER_MMSYSTEM departament :
         virtual public base_departament,
         virtual public ::user::interaction
      {
      public:



         enum EIds
         {

            IdsMuteAll,
            IdsMute

         };


         departament(sp(base_application) papp);
         virtual ~departament();


         virtual bool initialize1();



         bool initialize();


         bool finalize();





      };


   } // namespace mixguserbase


} // namespace multimedia






